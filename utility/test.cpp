#include "utility.hpp"
#include <iostream>
#include <vector>

int main() {
    openchat::utility::matrix a = {{0, 1, 2, 9}, 
                                   {3, 4, 5, 10}, 
                                   {6, 7, 8, 11}};
    
    for (std::vector<float> c : a) {
        for (float d : c) {
            std::cout << d << " ";
        }
        std::cout << std::endl;
    }
    
    openchat::utility::matrix b = openchat::utility::transpose(a, 3, 4);
    
    for (std::vector<float> c : b) {
        for (float d : c) {
            std::cout << d << " ";
        }
        std::cout << std::endl;
    }
    
    openchat::utility::matrix e = {{0, 1, 2}, 
    {3, 4, 5}, 
    {6, 7, 8},
    {9, 10, 11}};
    
    openchat::utility::matrix f = openchat::utility::dot(a, 3, 4, e, 4, 3);
    
    std::cout << "dot" << std::endl;
    for (std::vector<float> c : f) {
        for (float d : c) {
            std::cout << d << " ";
        }
        std::cout << std::endl;
    }
    
    openchat::utility::matrix g = openchat::utility::softmax(a);
    
    std::cout << "softmax" << std::endl;
    for (std::vector<float> c : g) {
        for (float d : c) {
            std::cout << d << " ";
        }
        std::cout << std::endl;
    }
}