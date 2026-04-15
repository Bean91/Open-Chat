#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

namespace openchat {
    class Tokenizer {
        private:
            std::vector<std::string> vocab = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ",", ".", "/", "<", ">", "?", ";", ":", "\'", "\'", "[", "]", "{", "}", "\\", "|", "-", "=", "_", "+", "`", "~", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "\n", "\t"};
            std::filesystem::path path;
            
            std::string escape(const std::string &token) {
                std::string output;
                for (char c : token) {
                    if (c == '\\') output += "\\\\";
                    else if (c == '\n') output += "\\n";
                    else if (c == '\t') output += "\\t";
                    else output += c;
                }
                return output;
            }
            
            std::string unescape(const std::string &token) {
                std::string output;
                for (int i = 0; i < token.length(); i++) {
                    if (token[i] == '\\' && i < token.length() - 1) {
                        if (token[i+1] == 'n') output += '\n';
                        else if (token[i+1] == 't') output += '\t';
                        else if (token[i+1] == '\\') output += '\\';
                        else {output += token[i]; i--;}
                        i++;
                    } else {
                        output += token[i];
                    }
                }
                return output;
            }
            

        public:
            Tokenizer(std::filesystem::path path, bool input = false) {
                this->path = path;
                if (input) {
                    vocab.clear();
                    
                    std::ifstream vocab_file(this->path);
                    std::string token_hold;
                    
                    while (getline(vocab_file, token_hold)) {
                        vocab.push_back(unescape(token_hold));
                    }
                }
            }
            
            std::filesystem::path get_path() {
                return this->path;
            }

            void set_path(std::filesystem::path path) {
                this->path = path;
            }

            std::vector<std::string> get_vocab() {
                return vocab;
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
                    save_file << escape(token) << std::endl;
                }
            }

            std::vector<int> encode(std::string text) {
                std::vector<int> tokens;
                
                auto find_token = [this](std::string tok) -> int {
                    for (int i = 0; i < this->vocab.size(); i++) {
                        if (tok == this->vocab.at(i)) return i;
                    }
                    return -1;
                };
                
                for (size_t i = 0; i < text.length(); i++) {
                    std::string hold;
                    hold = text[i];
                    
                    int j = 1;
                    while (i < text.length() - 1) {
                        if (find_token(hold + text[i+1]) != -1) {
                            j++;
                            hold += text[i+1];
                            i++;
                        } else {
                            break;
                        }
                    }

                    if (find_token(hold) == -1) break;
                    tokens.push_back(find_token(hold));
                }
                
                bool changed = false;
                while (changed) {
                    changed = false;
                    std::vector<int> merged_tokens;
                    for (size_t i = 0; i < tokens.size(); i++) {
                        std::string hold = vocab[tokens[i]];
                        while (i < tokens.size() - 1) {
                            if (find_token(hold+vocab[tokens[i+1]]) != -1) {
                                hold += vocab[tokens[i+1]];
                                i++;
                                changed=true;
                            } else {
                                break;
                            }
                        }
                        merged_tokens.push_back(find_token(hold));
                    }
                    tokens = merged_tokens;
                }
                
                return tokens;
            }
            
            std::string decode(std::vector<int> tokens) {
                std::string text;

                for (int token : tokens) {
                    text += this->vocab.at(token);
                }

                return text;
            }
    };
}

#endif