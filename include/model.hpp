#ifndef MODEL_HPP
#define MODEL_HPP

#include <forward_list>
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

            model(class tokenizer &tokenizer, class embedder &embedder, std::vector<class block> &blocks) {
                this->tokenizer = tokenizer;
                this->embedder = embedder;
                this->blocks = blocks;

                this->init();
            }

            std::string forwardPass(std::string input) {
                std::forward_list<int> tokens = tokenizer.encode(input);
                utility::matrix unembed = utility::transpose(*embedder.getTable());

                utility::matrix x = utility::matrix(std::distance(tokens.begin(), tokens.end()), embedder.getNEmbd());
                int i = 0;
                for (int token : tokens) {
                  std::vector<float> emb = embedder.embed(token);
                  std::copy(emb.begin(), emb.end(), x[i]);
                  i++;
                }
                
                x = positionalEncoding(x).apply();

                for (block b : this->blocks) {
                    x = b.feedForward(x);
                }

                utility::matrix dist = utility::matrix(1, embedder.getNEmbd());
                dist.data = std::vector<float>(x[x.rows - 1], x[x.rows - 1] + x.cols);

                dist = utility::softmax(utility::dot(dist, unembed));

                float max = dist[0][0];
                int token = 0;
                for (int i = 0; i < dist.rows; i++) {
                    if (dist[i][0] > max) {
                        max = dist[i][0];
                        token = i;
                    }
                }

                return tokenizer.decode({token});
            }
    };
}

#endif