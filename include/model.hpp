#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>
#include <filesystem>
#include <utility>
#include "tokenizer.hpp"
#include "embedder.hpp"
#include "positional_encoding.hpp"
#include "block.hpp"

namespace openchat {
    class model {
        private:
            tokenizer tokenizer;
            embedder embedder;
            positionalEncoding posEncode;
            std::vector<block> blocks;
            
        public:
            model(std::pair<std::pair<std::filesystem::path, std::filesystem::path>, std::vector<std::pair<std::vector<std::filesystem::path>, std::filesystem::path>>> inputFiles) : tokenizer(inputFiles.first.first), embedder(inputFiles.first.second) {
                for (size_t i = 0; i < inputFiles.second.size(); i++) {
                    blocks.push_back(block(inputFiles.second[i]));
                }
            }

            // model(tokenizer *tokenizer, ) {}
    };
}

#endif