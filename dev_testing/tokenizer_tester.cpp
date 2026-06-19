`#include` "../include/tokenizer.hpp"
`#include` <filesystem>
`#include` <forward_list>
`#include` <iostream>
`#include` <limits>
`#include` <ostream>
`#include` <string>

static void encode(openchat::tokenizer& tokenizer) {
    std::string input;

    std::cout << "Please enter a string to encode: " << std::endl;
    std::getline(std::cin, input);

    std::forward_list<int> tokens = tokenizer.encode(input);

    for (int token : tokens) {
        std::cout << token << " ";
    }
    std::cout << std::endl;
}

static void decode(openchat::tokenizer& tokenizer) {
    std::forward_list<int> input;
    auto tail = input.before_begin();
    int num = 0;
    int temp = 0;

    std::cout << "Please enter how many tokens you wish to decode: ";
    if (!(std::cin >> num) || num < 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Invalid token count." << std::endl;
        return;
    }

    std::cout << "Please enter the token IDs:" << std::endl;
    for (int i = 0; i < num; i++) {
        if (!(std::cin >> temp)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid token ID input." << std::endl;
            return;
        }
        tail = input.insert_after(tail, temp);
    }
    std::cout << "Decoded string:" << std::endl
                << tokenizer.decode(input) << std::endl;
}

int main() {
    openchat::tokenizer tokenizer = openchat::tokenizer("vocab.txt", true);

    char choose;

    while (true) {
        std::cout << "Choose something to do (use lowercase):" << std::endl
                    << " 1. Encode (e)" << std::endl
                    << " 2. Decode (d)" << std::endl
                    << " 3. Quit (q)" << std::endl;
        std::cin >> choose;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choose == 'e') encode(tokenizer);
        else if (choose == 'd') decode(tokenizer);
        else if (choose == 'q') break;
    }

    return 0;
}