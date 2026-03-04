#include <vector>
#include <iostream>
#include <stdexcept>

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
    };
}