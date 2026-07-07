#include <model.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

openchat::model init(openchat::tokenizer &tokenizer) {
    size_t n_embd = 256;
    openchat::embedder embedder(tokenizer.get_vocab()->size(), n_embd);

    std::cout << "Embedder initialized!" << std::endl;

    size_t n_blocks = 4;
    std::vector<openchat::block> blocks;

    std::vector<size_t> dimensions = {n_embd, n_embd * 4, n_embd};

    for (int i = 0; i < n_blocks; i++) {
        blocks.push_back({dimensions, n_embd});
        std::cout << "Block " << i << " initialized!" << std::endl;
    }

    return openchat::model(tokenizer, embedder, blocks);
}

std::pair<std::filesystem::path, std::vector<std::pair<std::pair<std::filesystem::path, std::vector<std::filesystem::path>>, std::filesystem::path>>> save() {
    std::filesystem::path embedder;
    size_t n_blocks;

    std::cout << "What is the file path to save the embedder?" << std::endl;
    std::cin >> embedder;

    std::cout << "How many attention blocks?" << std::endl;
    std::cin >> n_blocks;
    
    std::vector<std::pair<std::pair<std::filesystem::path, std::vector<std::filesystem::path>>, std::filesystem::path>> blocks;

    for (size_t i = 0; i < n_blocks; i++) {
        std::pair<std::pair<std::filesystem::path, std::vector<std::filesystem::path>>, std::filesystem::path> block;

        std::cout << "What is the file path to save the dimensions of the network?" << std::endl;
        std::cin >> block.first.first;

        size_t n_layers;
        std::cout << "How many layers in the network?" << std::endl;
        std::cin >> n_layers;

        block.first.second.resize(n_layers);

        for (size_t j = 0; j < n_layers; j++) {
            std::cout << "What is the file path to save layer " << j << "?" << std::endl;
            std::cin >> block.first.second.at(j);
        }

        std::cout << "What is the file path to save the attention matrices?" << std::endl;
        std::cin >> block.second;

        blocks.push_back(block);
    }

    return {embedder, blocks};
}

int main() {
	std::filesystem::path directory = "../training_corpus/english";
	openchat::tokenizer tokenizer = openchat::tokenizer("vocab.txt");

    openchat::model model = init(tokenizer);

    size_t epochs = 128;
    size_t chunks = 16384;
    size_t files = 512;
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

			if (fcounter >= files) break;
		}

		if (!corpus.empty()) {
			std::cout << "Starting global training. Total characters: " << corpus.length() << std::endl;
            size_t len = corpus.length() / chunks;
            for (size_t i = 0; i < chunks; i++) {
                std::string shortCorp = corpus.substr(i * len, (i + 1) * len);
			    model.train(shortCorp, epochs);
                if (i+1 % 16 == 0) std::cout << "Finished chunk " << i+1 << "/" << chunks << std::endl;
            }
		}
	} else {
		std::cerr << "Directory not found: " << directory << std::endl;
	}

	std::cout << "Training complete." << std::endl;
    model.saveToFile(save());
    std::cout << "Saved." << std::endl;

	return 0;
}