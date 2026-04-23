#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "neural_network.hpp"
#include "self_attention.hpp"

namespace openchat {
    class block {
        private:
            neuralNetwork network;
            selfAttention attention;
        public:
            void init() {
                this->network.init();
                this->attention.init();
            }

            void readFromFile(std::pair<std::vector<std::filesystem::path>, std::filesystem::path> input) {
                this->network.readFromFile(input.first);
                this->attention.readFromFile(input.second);
            }

            void saveToFile(std::pair<std::vector<std::filesystem::path>, std::filesystem::path> input) {
                this->network.saveToFile(input.first);
                this->attention.saveToFile(input.second);
            }

            block(std::vector<size_t> dimensions, size_t n_embd) : network(dimensions), attention(n_embd) {
                this->init();
            }

            block(std::pair<std::vector<std::filesystem::path>, std::filesystem::path> input) {
                this->readFromFile(input);
            }
    };
}

#endif