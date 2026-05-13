#ifndef SELF_ATTENTION_HPP
#define SELF_ATTENTION_HPP

#include "utility.hpp"
#include <filesystem>
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

            std::default_random_engine generator;
            std::normal_distribution<float> initDist;

          public:
            void init(size_t n_embd) {
                initDist = std::normal_distribution<float>(0, n_embd);

                for (size_t i = 0; i < n_embd; i++) {
                    for (size_t j = 0; j < n_embd; j++) {
                        this->wq[j][i] = initDist(this->generator);
                        this->wk[j][i] = initDist(this->generator);
                        this->wv[j][i] = initDist(this->generator);
                    }
                }
            }

            void readFromFile(std::filesystem::path input) {
                
            }

            void saveToFile(std::filesystem::path input) {

            }

            selfAttention(size_t n_embd) {
                this->wq = utility::matrix(n_embd, n_embd);
                this->wk = utility::matrix(n_embd, n_embd);
                this->wv = utility::matrix(n_embd, n_embd);

                this->init(n_embd);
            }

            utility::matrix attention(utility::matrix X, size_t d) {
                this->q = utility::dot(X, this->wq);
                this->k = utility::dot(X, this->wk);
                this->v = utility::dot(X, this->wv);
                
                return utility::dot(
                    utility::softmax(
                        utility::scalar_div(
                            utility::dot(this->q, 
                            utility::transpose(this->k)), 
                        std::sqrt(d))), 
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