#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <cstddef>
#include <vector>
#include <stdexcept>
#include <cmath>

namespace openchat {
    namespace utility {
        struct matrix {
            size_t rows, cols;
            std::vector<float> data;
        
            matrix(size_t r, size_t c) : rows(r), cols(c), data(r * c, 0.0f) {}
            matrix(): rows(0), cols(0), data(0, 0.0f) {}

            float* operator[](size_t row_index) {
                return &data[row_index * cols];
            }
        
            const float* operator[](size_t row_index) const {
                return &data[row_index * cols];
            }
        };
        
        matrix transpose(const matrix& input) {
            matrix output(input.cols, input.rows);
            for (size_t i = 0; i < input.rows; i++) {
                for (size_t j = 0; j < input.cols; j++) {
                    output[j][i] = input[i][j];
                }
            }
            return output;
        }

        matrix add(const matrix& a, const matrix& b) {
            if (a.cols != b.cols)
                throw std::invalid_argument("Columns don't match!");
            if (a.rows != b.rows)
                throw std::invalid_argument("Rows don't match!");
            
            matrix c = matrix(a.rows, b.cols);
            for (size_t i = 0; i < a.rows; i++ ) {
                for (size_t j = 0; j < a.cols; j++) {
                    c[i][j] = a[i][j] + b[i][j];
                }
            }

            return c;
        }
        
        matrix dot(const matrix& a, const matrix& b) {
            if (a.cols != b.rows) throw std::invalid_argument("Inner dimensions don't match!");
            
            matrix c(a.rows, b.cols);
            for (size_t i = 0; i < a.rows; i++) {
                for (size_t k = 0; k < a.cols; k++) {
                    float factor = a[i][k];
                    if (factor == 0.0f) continue;
                    for (size_t j = 0; j < b.cols; j++) {
                        c[i][j] += factor * b[k][j];
                    }
                }
            }
            return c;
        }        
        
        matrix softmax(matrix a) {
            for (size_t i = 0; i < a.rows; i++) {
                float max_val = a[i][0];
                for (size_t j = 1; j < a.cols; j++) {
                    if (a[i][j] > max_val) max_val = a[i][j];
                }

                float sum = 0.0f;
                for (size_t j = 0; j < a.cols; j++) {
                    a[i][j] = std::exp(a[i][j] - max_val);
                    sum += a[i][j];
                }
                
                for (size_t j = 0; j < a.cols; j++) {
                    a[i][j] /= sum; 
                }
            }
            return a;
        }
        
        matrix scalar_mult(matrix a, float b) {
            for (size_t i = 0; i < a.data.size(); i++) {
                a.data[i] *= b;
            }
            return a;
        }
        
        matrix scalar_div(matrix a, float b) {
            float inv_b = 1.0f / b;
            for (size_t i = 0; i < a.data.size(); i++) {
                a.data[i] *= inv_b;
            }
            return a;
        }

        float sigmoid(float x) {
            return 1.0f / (1.0f + std::exp(-x));
        }

        float gelu(float x) {
            return 0.5f * x * (1.0f + std::tanh(std::sqrt(2.0f / M_PI) * (x + 0.044715f * std::pow(x, 3))));
        }
    };
}

#endif
