#ifndef SELF_ATTENTION_HPP
#define SELF_ATTENTION_HPP

#include "utility.hpp"
#include <filesystem>
#include <fstream>
#include <random>

namespace openchat {
    class selfAttention {
        private:
            utility::matrix wq;
            utility::matrix wk;
            utility::matrix wv;
            
            utility::matrix q;
            utility::matrix k;
            utility::matrix v;

            size_t n_embd;

            std::default_random_engine generator;
            std::normal_distribution<float> initDist;

          public:
            void init() {
                initDist = std::normal_distribution<float>(0, this->n_embd);

                for (size_t i = 0; i < this->n_embd; i++) {
                    for (size_t j = 0; j < this->n_embd; j++) {
                        this->wq[j][i] = initDist(this->generator);
                        this->wk[j][i] = initDist(this->generator);
                        this->wv[j][i] = initDist(this->generator);
                    }
                }
            }

            void readFromFile(std::filesystem::path input) {
                std::ifstream inFile(input, std::ios::binary);

                if (inFile.is_open()) {
                    inFile.read(reinterpret_cast<char *>(&this->n_embd), sizeof(size_t));

                    this->wq = utility::matrix(this->n_embd, this->n_embd);
                    this->wk = utility::matrix(this->n_embd, this->n_embd);
                    this->wv = utility::matrix(this->n_embd, this->n_embd);

                    inFile.read(reinterpret_cast<char *>(this->wq.data.data()), this->wq.rows * this->wq.cols * sizeof(float));
                    inFile.read(reinterpret_cast<char *>(this->wk.data.data()), this->wk.rows * this->wk.cols * sizeof(float));
                    inFile.read(reinterpret_cast<char *>(this->wv.data.data()), this->wv.rows * this->wv.cols * sizeof(float));

                    inFile.close();
                }
            }

            void saveToFile(std::filesystem::path output) {
                std::ofstream outFile(output, std::ios::binary);

                if (outFile.is_open()) {
                    outFile.write(reinterpret_cast<const char *>(&this->n_embd), sizeof(size_t));

                    outFile.write(reinterpret_cast<const char *>(this->wq.data.data()), this->wq.rows * this->wq.cols * sizeof(float));
                    outFile.write(reinterpret_cast<const char *>(this->wk.data.data()), this->wk.rows * this->wk.cols * sizeof(float));
                    outFile.write(reinterpret_cast<const char *>(this->wv.data.data()), this->wv.rows * this->wv.cols * sizeof(float));

                    outFile.close();
                }
            }

            selfAttention(size_t n_embd) {
                this->wq = utility::matrix(n_embd, n_embd);
                this->wk = utility::matrix(n_embd, n_embd);
                this->wv = utility::matrix(n_embd, n_embd);
                
                this->n_embd = n_embd;

                this->init();
            }

            utility::matrix attention(utility::matrix x) {
                this->q = utility::dot(x, this->wq);
                this->k = utility::dot(x, this->wk);
                this->v = utility::dot(x, this->wv);
                
                return utility::dot(
                    utility::softmax(
                        utility::scalar_div(
                            utility::dot(this->q, 
                            utility::transpose(this->k)), 
                        std::sqrt(n_embd))), 
                    this->v); 
            }

            void changeOne(char mat, size_t row, size_t col, float d) {
                if (mat == 'q') wq[row][col] -= d;
                else if (mat == 'k') wk[row][col] -= d;
                else if (mat == 'v') wv[row][col] -= d;
            }

            selfAttention () {}
    };
}

#endif