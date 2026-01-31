#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace openchat {
    class Tokenizer {
        private:
            std::vector<std::string> vocab = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "`", "-", "=", "[", "]", "\\", ";", "'", ",", ".", "/", ")", "!", "@", "#", "$", "%", "^", "&", "*", "(", "~", "_", "+", "{", "}", "|", ":", "\"", "<", ">", "?", " ", "\\n", "é", "É", "à", "À", "è", "È", "ù", "Ù", "â", "Â", "ê", "Ê", "î", "Î", "ô", "Ô", "û", "Û", "ë", "Ë", "ï", "Ï", "ü", "Ü", "ç", "Ç", "œ", "Œ", "æ", "Æ"};
            fs::path path;
        public:
            Tokenizer(fs::path path) {
                this->path = path;
            }
            
            fs::path getPath() {
                return this->path;
            }

            void setPath(fs::path path) {
                this->path = path;
            }

            std::vector<std::string> getVocab() {
                return vocab;
            }

            void setVocab(std::vector<std::string> vocab) {
                this->vocab = vocab;
            }

            void addToken(std::string token) {
                this->vocab.push_back(token);
            }

            void saveTokens() {
                std::ofstream save_file(this->path);

                for (std::string token : vocab) {
                    save_file << token << std::endl;
                }
            }

            std::vector<int> encode(std::string text) {
                std::vector<int> tokens;
                
                auto find_token = [this](std::string tok) -> int {
                    for (int i; i < this->vocab.size(); i++) {
                        if (tok == this->vocab.at(i)) return i;
                    }
                    return -1;
                };
                
                for (size_t i; i < text.length(); i++) {
                    std::string hold;
                    
                    hold = text[i];
                    
                    while (i < text.length()) {
                        if (find_token(hold + text[i+1]) != -1) {
                            hold += text[i+1];
                            i++;
                        } else {
                            break;
                        }
                    }
                    
                    tokens.push_back(find_token(hold));
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