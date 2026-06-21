#ifndef LAYER_HPP
#define LAYER_HPP

#include "utility.hpp"
#include <filesystem>
#include <fstream>
#include <random>

namespace openchat {
    class layer {
        private:
            utility::matrix weights;
            utility::matrix biases;

            utility::matrix X;
            utility::matrix Z;

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
                std::ifstream inFile(input, std::ios::binary);

                if (inFile.is_open()) {
                    inFile.read(reinterpret_cast<char *>(&this->weights.rows), sizeof(size_t));
                    inFile.read(reinterpret_cast<char *>(&this->weights.cols), sizeof(size_t));
                    this->weights.data.resize(this->weights.rows * this->weights.cols);
                    inFile.read(reinterpret_cast<char *>(this->weights.data.data()), this->weights.rows * this->weights.cols * sizeof(float));

                    inFile.read(reinterpret_cast<char *>(&this->biases.rows), sizeof(size_t));
                    inFile.read(reinterpret_cast<char *>(&this->biases.cols), sizeof(size_t));
                    this->biases.data.resize(this->biases.rows * this->biases.cols);
                    inFile.read(reinterpret_cast<char *>(this->biases.data.data()), this->biases.rows * this->biases.cols * sizeof(float));

                    inFile.close();
                }
            }

            void saveToFile(std::filesystem::path output) {
                std::ofstream outFile(output, std::ios::binary);

                if (outFile.is_open()) {
                    outFile.write(reinterpret_cast<const char *>(&this->weights.rows), sizeof(size_t));
                    outFile.write(reinterpret_cast<const char *>(&this->weights.cols), sizeof(size_t));
                    outFile.write(reinterpret_cast<const char *>(this->weights.data.data()), this->weights.rows * this->weights.cols * sizeof(float));

                    outFile.write(reinterpret_cast<const char *>(&this->biases.rows), sizeof(size_t));
                    outFile.write(reinterpret_cast<const char *>(&this->biases.cols), sizeof(size_t));
                    outFile.write(reinterpret_cast<const char *>(this->biases.data.data()), this->biases.rows * this->biases.cols * sizeof(float));

                    outFile.close();
                }
            }

            layer(size_t n_in, size_t n_out) {
                this->weights = utility::matrix(n_in, n_out);
                this->biases = utility::matrix(1, n_out);

                this->init(n_in);
            }

            layer(std::filesystem::path input) {
                this->readFromFile(input);
            }

            utility::matrix feedForward(utility::matrix x) {
                this->X = x;
                utility::matrix z = utility::add(utility::dot(x, this->weights), this->biases);
                this->Z = z;
                for (size_t i = 0; i < z.rows; i++) for (size_t j = 0; j < z.cols; j++) z[i][j] = utility::relu(z[i][j]);
                return z;
            }

            std::pair<utility::matrix, std::pair<utility::matrix, utility::matrix>> backward(utility::matrix dZ) {
                int M = dZ.rows;
                int N = dZ.cols;

                utility::matrix dW = utility::dot(utility::transpose(this->X), dZ);
                utility::matrix dX = utility::dot(dZ, utility::transpose(this->weights));
        
                utility::matrix db(1, N); 
                std::fill(db.data.begin(), db.data.end(), 0.0f);
        
                for (int i = 0; i < M; ++i) {
                    for (int j = 0; j < N; ++j) {
                        db.data[j] += dZ.data[i * N + j];
                    }
                }
        
                return {dX, {dW, db}};
            }

            void changeOne(float d, size_t n_in, size_t n_out) {
                this->weights[n_in][n_out] -= d;
            }

            void changeOne(float d, size_t n_in) {
                this->biases[0][n_in] -= d;
            }
    };
}

#endif
