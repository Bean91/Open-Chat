#ifndef EMBEDDING_HPP
#define EMBEDDING_HPP

#include <cstddef>
#include <filesystem>
#include "utility.hpp"

namespace openchat {
    class embedder {
        private:
            utility::matrix table;
            size_t n_tok;
            size_t n_embd;
        public:
            void init() {
                
            }

            void readFromFile(std::filesystem::path input) {

            }

            void saveToFile(std::filesystem::path input) {

            }

            embedder(utility::matrix table, size_t n_tok, size_t n_embd) {
                this->table = table;
                this->n_tok = n_tok;
                this->n_embd = n_embd;
            }

            embedder(std::filesystem::path input) {
                this->readFromFile(input);
            }

            void changeOne(size_t tok, size_t dim, float d) {
                this->table[tok][dim] -= d;
            }

            std::vector<float> embed(size_t tok) {
                std::vector<float> vec(this->table[tok], this->table[tok]+n_embd);
                return vec;
            }
    };
}

#endif