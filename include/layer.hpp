#ifndef LAYER_HPP
#define LAYER_HPP

#include "utility.hpp"
#include <filesystem>
#include <random>

namespace openchat {
    class layer {
        private:
            utility::matrix weights;
            utility::matrix biases;
            std::default_random_engine generator;
            std::normal_distribution<float> initDist;

          public:
            void init(size_t n_in) {
                initDist = std::normal_distribution<float>(0, n_in);

                for (size_t i = 0; i < this->weights.cols; i++) {
                    this->biases[0][i] = initDist(this->generator);
                    for (size_t j = 0; j < this->weights.rows; j++) {
                        this->weights[j][i] = initDist(this->generator);
                    }
                }
            }

            void readFromFile(std::filesystem::path input) {

            }

            void saveToFile(std::filesystem::path input) {

            }

            layer(size_t n_in, size_t n_out) {
                this->weights = utility::matrix(n_in, n_out);
                this->biases = utility::matrix(1, n_out);

                this->init(n_in);
            }

            layer(std::filesystem::path input) {
                this->readFromFile(input);
            }

            std::vector<float> feedForward(std::vector<float> input) {
                utility::matrix i (1, input.size());
                i.data = input;
                std::vector<float> output = utility::add(utility::dot(i, this->weights), this->biases).data;
                for (size_t i = 0; i < output.size(); i++) {
                    output[i] = utility::relu(output[i]);
                }
                return output;
            }
    };
}

#endif
