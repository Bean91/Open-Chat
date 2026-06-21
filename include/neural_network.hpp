#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include <cstddef>
#include <filesystem>
#include <limits>
#include <vector>
#include "layer.hpp"
#include "utility.hpp"

namespace openchat {
    class neuralNetwork {
        private:
            std::vector<layer> network;
            std::vector<size_t> dimensions;

        public:
            void init() {
              for (size_t i = 0; i < dimensions.size() - 1; i++) {
                network.push_back(layer(dimensions[i], dimensions[i + 1]));
              }
            }

            void readFromFile(std::pair<std::filesystem::path, std::vector<std::filesystem::path>> input) {
                std::ifstream inFile(input.first, std::ios::binary);

                if (inFile.is_open()) {
                    inFile.read(reinterpret_cast<char *>(this->dimensions.data()), sizeof(size_t) * this->dimensions.size());
                }

                for (size_t i = 0; i < input.second.size(); i++) {
                    this->network.push_back(layer(input.second[i]));
                }
            }

            void saveToFile(std::pair<std::filesystem::path, std::vector<std::filesystem::path>> output) {
                std::ofstream outFile(output.first, std::ios::binary);

                if (outFile.is_open()) {
                    outFile.write(reinterpret_cast<char *>(this->dimensions.data()), sizeof(size_t) * this->dimensions.size());
                }

                for (size_t i = 0; i < output.second.size(); i++) {
                    this->network[i].saveToFile(output.second[i]);
                }
            }

            neuralNetwork(std::vector<size_t> dimensions) {
                this->dimensions = dimensions;

                this->init();
            }

            neuralNetwork(std::pair<std::filesystem::path, std::vector<std::filesystem::path>> input) {
                this->readFromFile(input);
            }

            void layerNorm(std::vector<float> &x, size_t start, size_t end) {
                std::vector<float> input(x[start], x[end]);

                if (input.empty()) return;

                float sum = 0;
                for (float i : input) sum += i;
                float mean = sum / input.size();

                sum = 0;
                for (float i : input) sum += (i-mean)*(i-mean);
                float variance = sum / input.size();

                for (int i = 0; i < input.size(); i++) {
                    input[i] = ((input[i] - mean)/std::sqrt(variance + std::numeric_limits<float>::epsilon()));
                }

                for (int i = 0; i < input.size(); i++) {
                    x[start+i] = input[i];
                }
            }

            utility::matrix feedForward(utility::matrix x) {
                for (layer &l : network) {
                    x = l.feedForward(x);
                }

                for (int i = 0; i < x.rows; i++) {
                    this->layerNorm(x.data, i*x.cols, i*x.cols+x.cols);
                }
                return x;
            }

            std::pair<utility::matrix, std::vector<std::pair<utility::matrix, utility::matrix>>> backward(utility::matrix dZ) {
                std::pair<utility::matrix, std::vector<std::pair<utility::matrix, utility::matrix>>> ndW;
                for (auto it = this->network.rbegin(); it != this->network.rend(); ++it) {
                    std::pair<utility::matrix, std::pair<utility::matrix, utility::matrix>> p = it->backward(dZ);
                    dZ = p.first;
                    ndW.second.push_back(p.second); 
                }
                ndW.first = dZ;
                return ndW;
            }

            void changeOne(size_t layer, float d, size_t n_in, size_t n_out) {
                this->network[layer].changeOne(d, n_in, n_out);
            }

            void changeOne(size_t layer, float d, size_t n_in) {
                this->network[layer].changeOne(d, n_in);
            }

            neuralNetwork() {}
    };
}

#endif