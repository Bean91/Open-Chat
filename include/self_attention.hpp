#ifndef SELF_ATTENTION_HPP
#define SELF_ATTENTION_HPP

#include "utility.hpp"
#include <filesystem>
#include <fstream>
#include <random>
#include <cmath>
#include <vector>
#include <utility>

namespace openchat {
    class selfAttention {
        private:
            utility::matrix wq;
            utility::matrix wk;
            utility::matrix wv;
            
            utility::matrix q;
            utility::matrix k;
            utility::matrix v;
            utility::matrix p;
            utility::matrix x;

            size_t n_embd;

            std::default_random_engine generator;
            std::normal_distribution<float> initDist;

          public:
            void init() {
                float stddev = 1.0f / std::sqrt(static_cast<float>(this->n_embd));
                initDist = std::normal_distribution<float>(0.0f, stddev);

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
                this->x = x;
                this->q = utility::dot(x, this->wq);
                this->k = utility::dot(x, this->wk);
                this->v = utility::dot(x, this->wv);

                this->p = utility::softmax(utility::scalar_div(
                    utility::dot(this->q, utility::transpose(this->k)),
                    std::sqrt(static_cast<float>(n_embd))));

                return utility::dot(this->p, this->v);
            }

            size_t getNEmbed() {
                return this->n_embd;
            }

            std::pair<utility::matrix, std::vector<utility::matrix>> backward(utility::matrix dZ) {
                utility::matrix dV = utility::dot(utility::transpose(this->p), dZ);
                utility::matrix dP = utility::dot(dZ, utility::transpose(this->v));
                
                int M = dP.rows; 
                utility::matrix dS(M, M);
                
                for (int i = 0; i < M; ++i) {
                    float sum_dP_P = 0.0f;

                    for (int k = 0; k < M; ++k) {
                        sum_dP_P += dP.data[i * M + k] * this->p.data[i * M + k];
                    }
                    
                    for (int j = 0; j < M; ++j) {
                        int idx = i * M + j;
                        dS.data[idx] = this->p.data[idx] * (dP.data[idx] - sum_dP_P);
                    }
                }
                
                int K = this->q.cols; 
                float scale = 1.0f / std::sqrt(static_cast<float>(K));
                for (int i = 0; i < M * M; ++i) {
                    dS.data[i] *= scale;
                }
                
                utility::matrix dQ = utility::dot(dS, this->k);
                utility::matrix dK = utility::dot(utility::transpose(dS), this->q);
                
                utility::matrix dWq = utility::dot(utility::transpose(this->x), dQ);
                utility::matrix dWk = utility::dot(utility::transpose(this->x), dK);
                utility::matrix dWv = utility::dot(utility::transpose(this->x), dV);
                
                utility::matrix dX_q = utility::dot(dQ, utility::transpose(this->wq));
                utility::matrix dX_k = utility::dot(dK, utility::transpose(this->wk));
                utility::matrix dX_v = utility::dot(dV, utility::transpose(this->wv));
                
                utility::matrix dX(dX_q.rows, dX_q.cols);
                for (int i = 0; i < dX.rows * dX.cols; ++i) {
                    dX.data[i] = dX_q.data[i] + dX_k.data[i] + dX_v.data[i];
                }
                
                std::vector<utility::matrix> weight_gradients = {dWq, dWk, dWv};
                return {dX, weight_gradients};
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
