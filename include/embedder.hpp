#ifndef EMBEDDER_HPP
#define EMBEDDER_HPP

#include <cstddef>
#include <filesystem>
#include <random>
#include <fstream>
#include "utility.hpp"

namespace openchat {
    class embedder {
        private:
            utility::matrix table;
            size_t n_tok;
            size_t n_embd;

            std::default_random_engine generator;
            std::normal_distribution<float> initDist;

          public:
            void init(float stddev = 0.02) {
                initDist = std::normal_distribution<float>(0, stddev);

                for (size_t i = 0; i < this->n_tok; i++) {
                    for (size_t j = 0; j < this->n_embd; j++) {
                        this->table[i][j] = initDist(this->generator);
                    }
                }
            }

            void readFromFile(std::filesystem::path input) {

            }

            void saveToFile(std::filesystem::path output) {
                std::ofstream outFile(output, std::ios::binary);

                if (outFile.is_open()) {
                    outFile.write(reinterpret_cast<const char *>(&this->n_tok), sizeof(size_t));
                    outFile.write(reinterpret_cast<const char *>(&this->n_embd), sizeof(size_t));

                    for (size_t i = 0; i < this->n_tok; i++) {
                        float * tok = this->table[i];
                        outFile.write(reinterpret_cast<const char*>(tok), this->n_embd * sizeof(float));
                    }
                    outFile.close();
                }
            }

            embedder(size_t n_tok, size_t n_embd) {
                this->n_tok = n_tok;
                this->n_embd = n_embd;

                this->table = utility::matrix(this->n_tok, this->n_embd);

                this->init();
            }

            embedder(std::filesystem::path input) {
              this->readFromFile(input);
            }

            void changeOne(size_t tok, size_t dim, float d) {
                this->table[tok][dim] -= d;
            }

            std::vector<float> embed(size_t tok) {
                std::vector<float> vec(this->table[tok], this->table[tok]+n_embd);
                return vec;
            }

            utility::matrix * getTable() {
                return &this->table;
            }

            embedder() {}
    };
}

#endif