#include "tokenizer.hpp"
#include <filesystem>
#include <iostream>
#include <map>
#include <string>
#include <utility>

namespace fs = std::filesystem;

namespace openchat {
	int train_on_file(Tokenizer *tokenizer, fs::path filepath, int epochs = 100) {
		std::map<std::pair<int, int>, int> frequency;
	
		std::ifstream training_file(filepath);
	
		std::string input;
		std::string line_hold;
	
		while (std::getline(training_file, line_hold)) {
			input += line_hold + "\n";
		}
	
		auto max_frequency = std::max_element(
			frequency.begin(),
			frequency.end(),
				[](const auto& a, const auto& b) {
				return a.second < b.second;
			}
		);
	
		for (int i = 0; i < epochs; i ++) {
			std::vector<int> encoded_tokens = tokenizer->encode(input);
	
			for (size_t j = 0; j < encoded_tokens.size() - 2; j++) {
				frequency[{encoded_tokens[j], encoded_tokens[j-1]}] += 1;
			}
	
			tokenizer->addToken(tokenizer->getVocab().at(max_frequency->first.first)+tokenizer->getVocab().at(max_frequency->first.second));
			frequency = {};
		}
	
		return 0;
	}
}

int main() {
	fs::path code_directory = "training_corpus/code";
	fs::path english_directory = "training_corpus/english";
	fs::path french_directory = "training_corpus/french";

	std::array<fs::path*, 3> directories = {&code_directory, &english_directory, &french_directory};

	openchat::Tokenizer tokenizer = openchat::Tokenizer("vocab.txt");

	for (fs::path * directory : directories) {
		if (fs::exists(*directory) && fs::is_directory(*directory)) {
			std::cout << *directory << std::endl;

			for (const fs::directory_entry& entry : fs::directory_iterator(*directory)) {
				train_on_file(&tokenizer, entry.path());
			}
		}
	}
	
	return 0;
}