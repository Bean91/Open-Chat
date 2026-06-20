#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "neural_network.hpp"
#include "self_attention.hpp"

namespace openchat {
    class block {
        private:
            neuralNetwork network;
            selfAttention attention;

            size_t n_embd;
        public:
            void init() {
                this->network.init();
                this->attention.init();
            }

            void readFromFile(std::pair<std::pair<std::filesystem::path, std::vector<std::filesystem::path>>, std::filesystem::path> input) {
                this->network.readFromFile(input.first);
                this->attention.readFromFile(input.second);
            }

            void saveToFile(std::pair<std::pair<std::filesystem::path, std::vector<std::filesystem::path>>, std::filesystem::path> output) {
                this->network.saveToFile(output.first);
                this->attention.saveToFile(output.second);
            }

            block(std::vector<size_t> dimensions, size_t n_embd) : network(dimensions), attention(n_embd) {
                this->init();

                this->n_embd = n_embd;
            }

            block(std::pair<std::pair<std::filesystem::path, std::vector<std::filesystem::path>>, std::filesystem::path> input) {
                this->readFromFile(input);
            }

            utility::matrix feedForward(utility::matrix x) {
                x = attention.attention(x);
                for (int i = 0; i < x.rows; i++) {
                    network.feedForward(std::vector<float>(x[i], x[i] + this->n_embd)).assign(x[i], x[i] + this->n_embd);
                }

                return x;
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