#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include <cstddef>
#include <filesystem>
#include <limits>
#include <vector>
#include "layer.hpp"

namespace openchat {
    class neuralNetwork {
        private:
            std::vector<layer> network;
            std::vector<size_t> dimensions;

            std::vector<float> gain;
            std::vector<float> bias;

        public:
            void init() {
              this->gain = std::vector<float>(this->dimensions[(this->dimensions.size() - 1)], 1.0f);
              this->bias = std::vector<float>(this->dimensions[(this->dimensions.size() - 1)], 0.0f);
              for (size_t i = 0; i < dimensions.size() - 1; i++) {
                network.push_back(layer(dimensions[i], dimensions[i + 1]));
              }
            }

            void readFromFile(std::pair<std::filesystem::path, std::vector<std::filesystem::path>> input) {
                std::ifstream inFile(input.first, std::ios::binary);

                if (inFile.is_open()) {
                    inFile.read(reinterpret_cast<char *>(this->dimensions.data()), sizeof(size_t) * this->dimensions.size());
                    inFile.read(reinterpret_cast<char *>(this->gain.data()), sizeof(float) * this->dimensions[(this->dimensions.size() - 1)]);
                    inFile.read(reinterpret_cast<char *>(this->bias.data()), sizeof(float) * this->dimensions[(this->dimensions.size() - 1)]);
                }

                for (size_t i = 0; i < input.second.size(); i++) {
                    this->network.push_back(layer(input.second[i]));
                }
            }

            void saveToFile(std::pair<std::filesystem::path, std::vector<std::filesystem::path>> output) {
                std::ofstream outFile(output.first, std::ios::binary);

                if (outFile.is_open()) {
                    outFile.write(reinterpret_cast<char *>(this->dimensions.data()), sizeof(size_t) * this->dimensions.size());
                    outFile.write(reinterpret_cast<char *>(this->gain.data()), sizeof(float) * this->dimensions[(this->dimensions.size() - 1)]);
                    outFile.write(reinterpret_cast<char *>(this->bias.data()), sizeof(float) * this->dimensions[(this->dimensions.size() - 1)]);
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

            void layerNorm(std::vector<float> &input) {
                if (input.empty()) return;

                float sum = 0;
                for (float i : input) sum += i;
                float mean = sum / input.size();

                sum = 0;
                for (float i : input) sum += (i-mean)*(i-mean);
                float variance = sum / input.size();

                for (int i = 0; i < input.size(); i++) {
                    input[i] = ((input[i] - mean)/std::sqrt(variance + std::numeric_limits<float>::epsilon())) * this->gain[i] + this->bias[i];
                }
            }

            std::vector<float> feedForward(std::vector<float> input) {
                for (layer &l : network) {
                    input = l.feedForward(input);
                }

                this->layerNorm(input);
                return input;
            }

            void changeOne(size_t layer, float d, size_t n_in, size_t n_out) {
                this->network[layer].changeOne(d, n_in, n_out);
            }

            void changeOne(size_t layer, float d, size_t n_in) {
                this->network[layer].changeOne(d, n_in);
            }
            
            void changeOne(int x, float d, int pos) {
                if (x == 0) gain[pos] -= d;
                if (x == 1) bias[pos] -= d;
            }

            neuralNetwork() {}
    };
}

#endif