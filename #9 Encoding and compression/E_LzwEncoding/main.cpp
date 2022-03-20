#include <iostream>
#include <string>
#include <map>
#include <vector>

std::map<std::string, int> *initializeMap() {
    auto map = new std::map<std::string, int>();

    for (int i = 0; i < 128; ++i) {
        map->insert({std::string(1, i), i});
    }

    return map;
}

std::vector<int> *lzwEncoding(const std::string &string_to_encode,
                              std::map<std::string, int> *dictionary) {
    auto answer = new std::vector<int>();
    std::string current_word;

    for (const char symbol : string_to_encode) {
        if (dictionary->find(current_word + symbol) == dictionary->end()) {
            answer->push_back(dictionary->at(current_word));
            dictionary->operator[](current_word + symbol) = dictionary->size();
            current_word = symbol;
        } else {
            current_word += symbol;
        }
    }

    answer->push_back(dictionary->at(current_word));

    return answer;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string input_line;
    std::getline(std::cin, input_line);

    auto map = initializeMap();

    auto vector = lzwEncoding(input_line, map);

    std::cout << vector->size() << '\n';

    for (int i = 0; i < vector->size(); ++i) {
        std::cout << vector->at(i) << ' ';
    }

    delete map;
    delete vector;
    return 0;
}
