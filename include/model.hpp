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

            model(class tokenizer &tokenizer, std::pair<std::filesystem::path, std::vector<std::pair<std::pair<std::filesystem::path, std::vector<std::filesystem::path>>, std::filesystem::path>>> inputFiles): embedder(inputFiles.first) {
                this->tokenizer = tokenizer;
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

            std::forward_list<int> tokenize(std::string input) {
                return this->tokenizer.encode(input);
            }

            std::string decodeToken(int tok) {
                return this->tokenizer.decode({tok});
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

            void train(std::string input, size_t epochs = 100) {
                std::forward_list<int> corpus = tokenizer.encode(input);
                auto length = std::distance(corpus.begin(), corpus.end());
                
                if (length < static_cast<long long>(epochs)) throw std::invalid_argument("Give a longer input!");
                size_t start = length - epochs;
            
                for (size_t i = 0; i < epochs; i++) {
                    std::forward_list<int> tokens(corpus.begin(), std::next(corpus.begin(), i + start));
                    int next = *std::next(corpus.begin(), i + start);
            
                    utility::matrix dist = forwardPass(tokens);
                    utility::matrix oneHot = utility::matrix(dist.rows, dist.cols);
                    oneHot[0][next] = 1;
                    float loss = -1 * std::log(dist[0][next]);
            
                    utility::matrix dZ = utility::subtract(dist, oneHot);
            
                    std::vector<std::pair<std::vector<std::pair<utility::matrix, utility::matrix>>, std::vector<utility::matrix>>> bdW;
                    utility::matrix edW;
            
                    for (auto it = blocks.rbegin(); it != blocks.rend(); ++it) {
                        std::pair<utility::matrix, std::pair<std::vector<std::pair<utility::matrix, utility::matrix>>, std::vector<utility::matrix>>> p = it->backward(dZ);
                        dZ = p.first;
                        bdW.push_back(p.second);
                    }
            
                    embedder.backward(dZ, this->learning_rate);

                    int j = 0;
                    for (auto it = this->blocks.rbegin(); it != this->blocks.rend(); ++it) {
                        block &b = *it;
                        std::vector<std::pair<utility::matrix, utility::matrix>> ndW = bdW[j].first;
                        std::vector<utility::matrix> adW = bdW[j].second;

                        for (size_t layer = 0; layer < ndW.size(); layer++) {
                            for (int k = 0; k < ndW[layer].first.cols; k++)
                                b.changeOne(layer, ndW[layer].first[0][k] * this->learning_rate, k);

                            for (int k = 0; k < ndW[layer].second.rows; k++)
                                for (int l = 0; l < ndW[layer].second.cols; l++)
                                    b.changeOne(layer, ndW[layer].second[k][l] * this->learning_rate, k, l);
                        }

                        for (int k = 0; k < adW[0].rows; k++)
                            for (int l = 0; l < adW[0].cols; l++)
                                b.changeOne('q', k, l, adW[0][k][l] * this->learning_rate);

                        for (int k = 0; k < adW[1].rows; k++)
                            for (int l = 0; l < adW[1].cols; l++)
                                b.changeOne('k', k, l, adW[1][k][l] * this->learning_rate);

                        for (int k = 0; k < adW[2].rows; k++)
                            for (int l = 0; l < adW[2].cols; l++)
                                b.changeOne('v', k, l, adW[2][k][l] * this->learning_rate);

                        j++;
                    }
                }
            }

            model() {}
            
    };
}

#endif