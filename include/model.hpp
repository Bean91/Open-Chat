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

            void saveToFile(std::pair<std::filesystem::path, std::vector<std::pair<std::pair<std::filesystem::path, std::vector<std::filesystem::path>>, std::filesystem::path>>> files) {
                embedder.saveToFile(files.first);

                for (int i = 0; i < blocks.size(); i++) {
                    blocks[i].saveToFile(files.second[i]);
                }
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

            struct forwardResult {
                utility::matrix dist;        // softmax output over the vocab, shape (1, n_vocab)
                utility::matrix unembed;     // transpose of the embedding table, shape (n_embd, n_vocab)
                utility::matrix lastHidden;  // last-position hidden state fed into unembed, shape (1, n_embd)
                size_t seq_len;              // number of positions the blocks were run over
            };

            forwardResult forwardPassInternal(std::forward_list<int> tokens) {
                utility::matrix unembed = utility::transpose(*embedder.getTable());

                utility::matrix x = embedder.embed(tokens);

                x = positionalEncoding(x).apply();

                for (block &b : this->blocks) {
                    x = b.feedForward(x);
                }

                utility::matrix lastHidden = utility::matrix(1, embedder.getNEmbd());
                lastHidden.data = std::vector<float>(x[x.rows - 1], x[x.rows - 1] + x.cols);

                utility::matrix dist = utility::softmax(utility::dot(lastHidden, unembed));

                return {dist, unembed, lastHidden, x.rows};
            }

            utility::matrix forwardPass(std::forward_list<int> tokens) {
                return forwardPassInternal(tokens).dist;
            }

            void train(std::string input, size_t epochs = 100) {
                std::forward_list<int> corpus = tokenizer.encode(input);
                auto length = std::distance(corpus.begin(), corpus.end());
                
                if (length < static_cast<long long>(epochs)) throw std::invalid_argument("Give a longer input!");
                size_t start = length - epochs;
            
                for (size_t i = 0; i < epochs; i++) {
                    std::forward_list<int> tokens(corpus.begin(), std::next(corpus.begin(), i + start));
                    int next = *std::next(corpus.begin(), i + start);
            
                    forwardResult fr = forwardPassInternal(tokens);
                    utility::matrix dist = fr.dist;
                    utility::matrix oneHot = utility::matrix(dist.rows, dist.cols);
                    oneHot[0][next] = 1;
                    float loss = -1 * std::log(dist[0][next]);

                    utility::matrix dLogits = utility::subtract(dist, oneHot);

                    utility::matrix dUnembed = utility::dot(utility::transpose(fr.lastHidden), dLogits);
                    utility::matrix dTable = utility::transpose(dUnembed);
                    utility::matrix *table = embedder.getTable();
                    for (size_t row = 0; row < dTable.rows; row++) {
                        for (size_t col = 0; col < dTable.cols; col++) {
                            (*table)[row][col] -= dTable[row][col] * this->learning_rate;
                        }
                    }

                    utility::matrix dHidden = utility::dot(dLogits, utility::transpose(fr.unembed));

                    utility::matrix dZ(fr.seq_len, embedder.getNEmbd());
                    for (size_t col = 0; col < dHidden.cols; col++) {
                        dZ[fr.seq_len - 1][col] = dHidden[0][col];
                    }

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