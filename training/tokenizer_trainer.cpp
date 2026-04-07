#include "tokenizer.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>

namespace openchat {
	int train_on_file(Tokenizer *tokenizer, std::filesystem::path filepath, int epochs = 100) {
		std::map<std::pair<int, int>, int> frequency;
	
		std::ifstream training_file(filepath);
	
		std::string input;
		std::string line_hold;
	
		while (std::getline(training_file, line_hold)) {
			input += line_hold + "\n";
		}
	
		for (int i = 0; i < epochs; i ++) {
			frequency.clear();
			std::vector<int> encoded_tokens = tokenizer->encode(input);
			
			for (size_t j = 0; j < encoded_tokens.size() - 1; j++) {
				frequency[{encoded_tokens[j], encoded_tokens[j+1]}]++;
			}
			
			if (frequency.empty()) break;
			
			std::pair<std::pair<int, int>, int> max_frequency = {{-1, -1}, -1};

			for (const auto& [pair, count] : frequency) {
				if (count > max_frequency.second) {
					std::string candidate = tokenizer->get_vocab().at(pair.first) + 
											tokenizer->get_vocab().at(pair.second);
     
					bool exists = false;
					const std::vector<std::string>& v = tokenizer->get_vocab();
					for (const std::string& s : v) {
						if (s == candidate) {
							exists = true;
							break;
						}
					}
					
					if (!exists) {
						max_frequency.second = count;
						max_frequency.first = pair;
					}
				}
			}
			
			std::string new_token = tokenizer->get_vocab().at(max_frequency.first.first) + 
				tokenizer->get_vocab().at(max_frequency.first.second);
				tokenizer->add_token(new_token);
		}
	
		return 0;
	}
}

int main() {
	std::filesystem::path code_directory = "../training_corpus/code";
	std::filesystem::path english_directory = "../training_corpus/english";
	std::filesystem::path french_directory = "../training_corpus/french";

	std::array<std::filesystem::path*, 3> directories = {&code_directory, &english_directory, &french_directory};

	openchat::Tokenizer tokenizer = openchat::Tokenizer("vocab.txt");

	for (std::filesystem::path * directory : directories) {
		if (std::filesystem::exists(*directory) && std::filesystem::is_directory(*directory)) {
			std::cout << *directory << std::endl;
			int fcounter = 0;

			for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(*directory)) {
				train_on_file(&tokenizer, entry.path(), 10);
				fcounter++;
				if (fcounter % 50 == 0) std::cout << "File number: " << fcounter << std::endl;
				if (fcounter >= 500) break;
			}
		}
	}
	
	tokenizer.save_tokens();
	
	return 0;
}