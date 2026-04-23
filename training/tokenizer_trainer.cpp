#include "../include/tokenizer.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <forward_list>

namespace openchat {
	void combine_token(std::forward_list<int>& encoded_tokens, int first, int second, int k) {
		auto start = encoded_tokens.begin();
		auto end = encoded_tokens.end();
		auto next = std::next(start);
		while (next != end) {
			if (*start == first && *next == second) {
				*start = k;
				next = encoded_tokens.erase_after(start);
			} else {
				start = next;
				next++;
			}
		}
	}

	int train_on_string(tokenizer *tokenizer, std::string input, int epochs = 100) {
		std::forward_list<int> encoded_tokens = tokenizer->encode(input);
		for (int i = 0; i < epochs; i++) {
			std::map<std::pair<int, int>, int> frequency;

			if (!encoded_tokens.empty()) {
				auto current = encoded_tokens.begin();
				auto next = std::next(current);
			
				while (next != encoded_tokens.end()) {
					frequency[{*current,*next}]++;
					current++;
					next++;
				}
			}

			std::pair<int, int> best_pair = {-1, -1};
			int max_count = 0;

			for (auto const &[pair, count] : frequency) {
				std::string combo = tokenizer->get_vocab()->at(pair.first)+tokenizer->get_vocab()->at(pair.second);
				if (std::find(tokenizer->get_vocab()->begin(), tokenizer->get_vocab()->end(), combo) != tokenizer->get_vocab()->end()) break;
				if (count > max_count) {
					if (pair.first >= 0 && pair.second >= 0) {
						max_count = count;
						best_pair = pair;
					}
				}
			}

			if (max_count > 0 && best_pair.first != -1) {
				std::string new_token = tokenizer->get_vocab()->at(best_pair.first) + tokenizer->get_vocab()->at(best_pair.second);
				combine_token(encoded_tokens, best_pair.first, best_pair.second, tokenizer->get_vocab()->size());
				std::cout << new_token << std::endl;
				tokenizer->add_token(new_token);
			} else {
				break;
			}

			if (tokenizer->get_vocab()->size() % 32 == 0) std::cout << "Vocab size: " << tokenizer->get_vocab()->size() << std::endl;
        }
		return 0;
	}
}

int main() {
	std::filesystem::path directory = "../training_corpus/english";
	openchat::tokenizer tokenizer = openchat::tokenizer("vocab.txt");

	std::string corpus = "";

	if (std::filesystem::exists(directory) && std::filesystem::is_directory(directory)) {
		std::cout << "Reading directory: " << directory << std::endl;
		int fcounter = 0;

		for (const std::filesystem::directory_entry &entry : std::filesystem::directory_iterator(directory)) {
			std::ifstream training_file(entry.path());
			if (training_file.is_open()) {
				std::stringstream buffer;
				buffer << training_file.rdbuf();

				corpus += buffer.str() + " ";

				fcounter++;
				if (fcounter % 32 == 0) std::cout << "Loaded " << fcounter << " files..." << std::endl;
			}

			if (fcounter >= 256) break;
		}

		if (!corpus.empty()) {
			std::cout << "Starting global training. Total characters: " << corpus.length() << std::endl;
			openchat::train_on_string(&tokenizer, corpus, 1951);
		}
	} else {
		std::cerr << "Directory not found: " << directory << std::endl;
	}

	std::cout << "Training complete. Final Vocab Size: " << tokenizer.get_vocab()->size() << std::endl;
	tokenizer.save_tokens();

	return 0;
}