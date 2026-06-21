#ifndef EMBEDDER_HPP
#define EMBEDDER_HPP

#include <cstddef>
#include <filesystem>
#include <forward_list>
#include <random>
#include <fstream>
#include "utility.hpp"

namespace openchat {
    class embedder {
        private:
            utility::matrix table;
            size_t n_tok;
            size_t n_embd;

            std::forward_list<int> toks;

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
                std::ifstream inFile(input, std::ios::binary);

                if (inFile.is_open()) {
                    inFile.read(reinterpret_cast<char *>(&this->n_tok), sizeof(size_t));
                    inFile.read(reinterpret_cast<char *>(&this->n_embd),sizeof(size_t));

                    this->table = utility::matrix(this->n_tok, this->n_embd);

                    for (size_t i = 0; i < this->n_tok; i++) {
                      inFile.read(reinterpret_cast<char *>(this->table[i]), this->n_embd * sizeof(float));
                    }
                    inFile.close();
                }
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

            size_t getNEmbd() {
                return this->n_embd;
            }

            void changeOne(size_t tok, size_t dim, float d) {
                this->table[tok][dim] -= d;
            }

            std::vector<float> embed(int tok) {
                if (tok < 0 || static_cast<size_t>(tok) >= this->n_tok) {
                    throw std::out_of_range("Token index out of bounds");
                }
                std::vector<float> vec(this->table[tok], this->table[tok]+n_embd);
                return vec;
            }

            utility::matrix embed(std::forward_list<int> toks) {
                this->toks = toks;
                utility::matrix vec(std::distance(toks.begin(), toks.end()), this->n_embd);
                int i = 0;
                for (int tok : toks) {
                  std::vector<float> emb = this->embed(tok);
                  std::copy(emb.begin(), emb.end(), vec[i]);
                  i++;
                }

                return vec;
            }

            utility::matrix * getTable() {
                return &this->table;
            }

            void backward(utility::matrix dZ, float lr) {
                auto tok_it = this->toks.begin();
                for (int i = 0; i < dZ.rows; i++) {
                    int tok = *tok_it;
                    for (int j = 0; j < dZ.cols; j++) {
                        this->table[tok][j] -= dZ[i][j] * lr;
                    }
                    +tok_it;
                }
            }

            embedder() {}
    };
}

#endif