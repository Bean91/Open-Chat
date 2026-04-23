#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include <cstddef>
#include <filesystem>
#include <vector>
#include "layer.hpp"

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

            void readFromFile(std::vector<std::filesystem::path> input) {
                for (size_t i = 0; i < input.size(); i++) {
                    this->network.push_back(layer(input[i]));
                }
            }

            void saveToFile(std::vector<std::filesystem::path> input) {
                for (size_t i = 0; i < input.size(); i++) {
                    this->network[i].saveToFile(input[i]);
                }
            }

            neuralNetwork(std::vector<size_t> dimensions) {
                this->dimensions = dimensions;

                this->init();
            }

            neuralNetwork(std::vector<std::filesystem::path> input) {
                this->readFromFile(input);
            }

            std::vector<float> feedForward(std::vector<float> input) {
                for (layer &l : network) {
                    input = l.feedForward(input);
                }

                return input;
            }

            void changeOne(size_t layer, float d, size_t n_in, size_t n_out) {
                this->network[layer].changeOne(d, n_in, n_out);
            }

            void changeOne(size_t layer,float d, size_t n_in) {
                this->network[layer].changeOne(d, n_in);
            }

            neuralNetwork() {}
    };
}

#endif