#ifndef MODEL_HPP
#define MODEL_HPP

#include <cstddef>
#include <forward_list>
#include <stdexcept>
#include <vector>
#include <filesystem>
#include <utility>
#include "tokenizer.hpp"
#include "embedder.hpp"
#include "positional_encoding.hpp"
#include "block.hpp"
#include "utility.hpp"

namespace openchat {
    class model {
        private:
            tokenizer tokenizer;
            embedder embedder;
            std::vector<block> blocks;
            float learning_rate = 0.01;
            
        public:
            void init() {
                this->embedder.init();

                for (block& b : this->blocks) {
                    b.init();
                }
            }

            model(std::pair<std::pair<std::filesystem::path, std::filesystem::path>, std::vector<std::pair<std::pair<std::filesystem::path, std::vector<std::filesystem::path>>, std::filesystem::path>>> inputFiles) : tokenizer(inputFiles.first.first, true), embedder(inputFiles.first.second) {
                for (size_t i = 0; i < inputFiles.second.size(); i++) {
                    blocks.push_back(block(inputFiles.second[i]));
                }
            }

            model(class tokenizer &tokenizer, class embedder &embedder, std::vector<class block> &blocks, float learning_rate = 0.01) {
                this->tokenizer = tokenizer;
                this->embedder = embedder;
                this->blocks = blocks;

                this->learning_rate = learning_rate;

                this->init();
            }

            void changeLearningRate(float n) {
                this->learning_rate = n;
            }

            utility::matrix forwardPass(std::forward_list<int> tokens) {
                utility::matrix unembed = utility::transpose(*embedder.getTable());

                utility::matrix x = embedder.embed(tokens);
                
                x = positionalEncoding(x).apply();

                for (block b : this->blocks) {
                    x = b.feedForward(x);
                }

                utility::matrix dist = utility::matrix(1, embedder.getNEmbd());
                dist.data = std::vector<float>(x[x.rows - 1], x[x.rows - 1] + x.cols);

                dist = utility::softmax(utility::dot(dist, unembed));

                return dist;
            }

            void backward(std::string input, size_t epochs = 100) {
                std::forward_list<int> corpus = tokenizer.encode(input);
                auto length = std::distance(corpus.begin(), corpus.end());
                
                if (length < static_cast<long long>(epochs)) throw std::invalid_argument("Give a longer input!");
                size_t start = length - epochs;
            
                for (size_t i = 0; i < epochs; i++) {
                    std::forward_list<int> tokens(corpus.begin(), std::next(corpus.begin(), i + start));
                    int next = *std::next(corpus.begin(), i + start);
            
                    utility::matrix dist = forwardPass(tokens);
                    utility::matrix oneHot = utility::matrix(dist.rows, 1);
                    oneHot[next][0] = 1;
                    float loss = -1 * std::log(dist[next][0]);
            
                    utility::matrix dZ = utility::subtract(dist, oneHot);
            
                    std::vector<std::pair<std::vector<utility::matrix>, std::vector<utility::matrix>>> bdW;
                    utility::matrix edW;
            
                    for (auto it = blocks.rbegin(); it != blocks.rend(); ++it) {
                        std::pair<utility::matrix, std::pair<std::vector<utility::matrix>, std::vector<utility::matrix>>> p = it->backward(dZ);
                        dZ = p.first;
                        bdW.push_back(p.second);
                    }
            
                    embedder.backward(dZ, this->learning_rate);
                }
            }
            
    };
}

#endif