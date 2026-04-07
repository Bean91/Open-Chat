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

            void readFromFile(std::filesystem::path input) {

            }

            void saveToFile(std::filesystem::path input) {

            }

            neuralNetwork(std::vector<size_t> dimensions) {
                this->dimensions = dimensions;

                this->init();
            }

            neuralNetwork(std::filesystem::path input) {
                this->readFromFile(input);
            }

            std::vector<float> feedForward(std::vector<float> input) {
                for (layer &l : network) {
                    input = l.feedForward(input);
                }

                return input;
            }
    };
}

#endif