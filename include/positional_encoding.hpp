#ifndef POSITIONAL_ENCODING_HPP
#define POSITIONAL_ENCODING_HPP

#include <cstddef>
#include "utility.hpp"

namespace openchat {
    class positionalEncoding {
        private:
            size_t n_embd;
            size_t n_in;
            utility::matrix table;
            utility::matrix x;
        public:
            positionalEncoding() {}

            positionalEncoding(utility::matrix x) {
                this->x = x;
                this->n_in = x.rows;
                this->n_embd = x.cols;

                for (size_t i = 0; i < this->n_in; i++) {
                    for (size_t j = 0; j < this->n_embd/2; j++) {
                        this->table[i][2*j] = std::sin(i/std::pow(10000,2.0*j/this->n_embd));
                        this->table[i][2*j+1] = std::cos(i/std::pow(10000,2.0*j/this->n_embd));
                    }
                }
            }

            utility::matrix apply() {
                return utility::add(x, table);
            }
    };
}

#endif