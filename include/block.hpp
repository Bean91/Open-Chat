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
            void init(size_t n_embd) {
                this->network.init();
                this->attention.init(n_embd);
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
                this->init(n_embd);
            }

            block(std::pair<std::vector<std::filesystem::path>, std::filesystem::path> input) {
                this->readFromFile(input);
            }

            void changeOne(char mat, size_t row, size_t col, float d) {
                this->attention.changeOne(mat, row, col, d);
            }

            void changeOne(size_t layer, float d, size_t n_in, size_t n_out) {
                this->network.changeOne(layer, d, n_in, n_out);
            }

            void changeOne(size_t layer,float d, size_t n_in) {
                this->network.changeOne(layer, d, n_in);
            }
    };
}

#endif