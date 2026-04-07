#ifndef LAYER_HPP
#define LAYER_HPP

#include <utility>
#include <vector>
#include "utility.hpp"

namespace openchat {
    class layer {
        private:
            utility::matrix weights;
            utility::matrix biases;

          public:
            void init() {

            }

            layer(size_t n_in, size_t n_out) {
                this->weights = utility::matrix(n_in, n_out);
                this->biases = utility::matrix(1, n_out);

                this->init();
            }
            
            layer(utility::matrix weights, utility::matrix biases) {
                this->weights = weights;
                this->biases = biases;
            }

            std::vector<float> feedForward(std::vector<float> input) {
                utility::matrix i (1, input.size());
                i.data = input;
                return utility::add(utility::dot(i, this->weights), this->biases).data;
            }

            std::pair<utility::matrix *, utility::matrix *> getData() { return {&this->weights, &this->biases}; }
    };
}

#endif
