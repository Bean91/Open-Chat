#include <cstddef>
#include <string>
#include <iostream>
#include <model.hpp>

openchat::model init(openchat::tokenizer &tokenizer) {
    size_t n_embd;
    openchat::embedder embedder(tokenizer.get_vocab()->size(), n_embd);

    size_t n_blocks = 4;
    std::vector<openchat::block> blocks;

    std::vector<size_t> dimensions = {n_embd, n_embd * 4, n_embd};

    for (int i = 0; i < n_blocks; i++) {
        blocks.push_back({dimensions, n_embd});
    }

    return openchat::model(tokenizer, embedder, blocks);
}

openchat::model read(openchat::tokenizer&tokenizer) {
    std::filesystem::path embedder;
    size_t n_blocks;

    std::cout << "What is the file path for the embedder?" << std::endl;
    std::cin >> embedder;

    std::cout << "How many attention blocks?" << std::endl;
    std::cin >> n_blocks;
    
    std::vector<std::pair<std::pair<std::filesystem::path, std::vector<std::filesystem::path>>, std::filesystem::path>> blocks;

    for (size_t i = 0; i < n_blocks; i++) {
        std::pair<std::pair<std::filesystem::path, std::vector<std::filesystem::path>>, std::filesystem::path> block;

        std::cout << "What is the file path for the dimensions of the network?" << std::endl;
        std::cin >> block.first.first;

        size_t n_layers;
        std::cout << "How many layers in the network?" << std::endl;
        std::cin >> n_layers;

        block.first.second.resize(n_layers);

        for (size_t j = 0; j < n_layers; j++) {
            std::cout << "What is the file path for layer " << j << "?" << std::endl;
            std::cin >> block.first.second.at(j);
        }

        std::cout << "What is the file path for the attention matrices?" << std::endl;
        std::cin >> block.second;

        blocks.push_back(block);
    }

    return openchat::model(tokenizer, {embedder, blocks});
}

void predict(openchat::model &model) {
    std::string input;
    std::cout << "What would you like to input?" << std::endl;
    std::cin >> input;
    
    std::forward_list<int> tokens = model.tokenize(input);

    openchat::utility::matrix dist = model.forwardPass(tokens);

    float max = dist[0][0];
    size_t maxi = 0;
    for (size_t i = 0; i < dist.rows; i++) {
        if (dist[i][0] > max) {
            max = dist[i][0];
            maxi = i;
        }
    }

    std::cout << "Predicted token: " <<  model.decodeToken(maxi) << std::endl;
}

int main() {
    openchat::tokenizer tokenizer = openchat::tokenizer("vocab.txt", true);
    openchat::model model;
    char choose;

    std::cout << "(i)nitialize new model or (r)ead from model files?" << std::endl;

    std::cin >> choose;

    if (choose == 'i') model = init(tokenizer);
    else if (choose == 'r') model = read(tokenizer);

    while (true) {
        std::cout << "Choose something to do (use lowercase):" << std::endl
                    << " 1. Predict (p)" << std::endl
                    << " 2. Train (t)" << std::endl
                    << " 3. Quit (q)" << std::endl;
        std::cin >> choose;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choose == 'p') predict(model);
        else if (choose == 't') std::cout << "Please use model_trainer executable!" << std::endl;
        else if (choose == 'q') break;
    }

    return 0;
}