#ifndef SELF_ATTENTION_HPP
#define SELF_ATTENTION_HPP

#include "utility.hpp"
#include <filesystem>

namespace openchat {
    class selfAttention {
        private:
            utility::matrix wq;
            utility::matrix wk;
            utility::matrix wv;
            
            utility::matrix q;
            utility::matrix k;
            utility::matrix v;
        public:
            void init() {

            }

            void readFromFile(std::filesystem::path input) {
                
            }

            void saveToFile(std::filesystem::path input) {

            }

            selfAttention(utility::matrix wq, utility::matrix wk, utility::matrix wv) {
                this->wq = wq;
                this->wk = wk;
                this->wv = wv;
            }

            selfAttention(std::filesystem::path input) {
              this->readFromFile(input);
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

            void update(char mat, size_t row, size_t col, float diff) {
                if (mat == 'q') wq[row][col] -= diff;
                else if (mat == 'k') wk[row][col] -= diff;
                else if (mat == 'v') wv[row][col] -= diff;
            }
    };
}

#endif