#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath>

namespace openchat {
    namespace utility {
        typedef std::vector<std::vector<float>> matrix;
        
        matrix transpose(matrix input, size_t n, size_t m) {
            matrix output;
            output.resize(m);
            for (int i = 0; i < m; i++) {
                output[i].resize(n);
            }
            
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    output[j][i] = input[i][j];
                }
            }
            
            return output;
        }
        
        matrix dot(matrix a, size_t na, size_t ma, matrix b, size_t nb, size_t mb) {
            if (ma != nb) throw std::invalid_argument("Inner dimensions don't match!");
            matrix c;
            c.resize(na);
            for (int i = 0; i < na; i++) {
                c[i].resize(mb);
            }
            
            for (int i = 0; i < na; i++) {
                for (int k = 0; k < ma; k++) {
                    float factor = a[i][k];
                    for (int j = 0; j < mb; j++) {
                        c[i][j] += factor * b[k][j];
                    }
                }
            }
            
            return c;
        }
        
        matrix softmax(matrix a) {
            std::vector<float> col_sums;
            col_sums.resize(a.size());
            
            for (int i = 0; i < a.size(); i++) {
                float max_val = *std::max_element(a[i].begin(), a[i].end());
                for (int j = 0; j < a[i].size(); j++) {
                    a[i][j] = std::exp(a[i][j] - max_val);
                    col_sums[i] += a[i][j]; 
                }
                
                for (int k = 0; k < a[i].size(); k++) {
                    a[i][k] /= col_sums[i]; 
                }
            }
            
            return a;
        }
        
        matrix scalar_mult(matrix a, float b) {
            for (int i = 0; i < a.size(); i++) {
                for (int j = 0; j < a[i].size(); j++) {
                    a[i][j] *= b;
                }
            }
            
            return a;
        }
        
        matrix scalar_div(matrix a, float b) {
            for (int i = 0; i < a.size(); i++) {
                for (int j = 0; j < a[i].size(); j++) {
                    a[i][j] /= b;
                }
            }
            
            return a;
        }
    };
}