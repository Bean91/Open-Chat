#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <filesystem>
#include <forward_list>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>

namespace openchat {
    class tokenizer {
        private:
            std::vector<std::string> vocab = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ",", ".", "/", "<", ">", "?", ";", ":", "\"", "\'", "[", "]", "{", "}", "\\", "|", "-", "=", "_", "+", "`", "~", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "\n", "\t", " "};
            std::filesystem::path path;

        public:
            tokenizer(std::filesystem::path path, bool input = false) {
                this->path = path;
                if (input) {
                    vocab.clear();
                    
                    std::ifstream vocab_file(this->path);
                    std::string token_hold;
                    
                    while (getline(vocab_file, token_hold)) {
                        vocab.push_back(token_hold);
                    }
                }
            }
            
            std::filesystem::path get_path() {
                return this->path;
            }

            void set_path(std::filesystem::path path) {
                this->path = path;
            }

            std::vector<std::string>* get_vocab() {
                return &vocab;
            }

            void set_vocab(std::vector<std::string> vocab) {
                this->vocab = vocab;
            }

            void add_token(std::string token) {
                if (std::find(this->vocab.begin(), this->vocab.end(), token) != this->vocab.end()) {
                    return; 
                }
                this->vocab.push_back(token);
            }

            void save_tokens() {
                std::ofstream save_file(this->path);

                for (std::string token : vocab) {
                    save_file << token << std::endl;
                }
            }

            std::forward_list<int> encode(std::string text) {
                std::forward_list<int> tokens;
                auto tail = tokens.before_begin();
            
                std::unordered_map<std::string, int> token_to_id;
                for (size_t i = 0; i < vocab.size(); i++) {
                    token_to_id[vocab[i]] = i;
                }
            
                for (size_t i = 0; i < text.length(); i++) {
                    std::string hold(1, text[i]);
                    int best_id = -1;
                    std::string best_match = "";
            
                    if (token_to_id.count(hold)) {
                        best_id = token_to_id[hold];
                        best_match = hold;
            
                        std::string candidate = hold;
                        for (size_t lookahead = i + 1; lookahead < text.length(); lookahead++) {
                            candidate += text[lookahead];
                            if (token_to_id.count(candidate)) {
                                best_id = token_to_id[candidate];
                                best_match = candidate;
                            } else {
                                break;
                            }
                        }
                    }
            
                    if (best_id != -1) {
                        tail = tokens.insert_after(tail, best_id); 
                        i += (best_match.length() - 1);
                    } else {
                        std::cerr << "Unknown char: " << text[i] << std::endl;
                    }
                }
                return tokens;
            }
            

            std::string decode(std::forward_list<int> tokens) {
                std::string text;

                for (int token : tokens) {
                    text += this->vocab.at(token);
                }

                return text;
            }

            tokenizer() {}
    };
}

#endif