#include <iostream>
#include <string>
#include <map>
#include <vector>

std::map<int, std::string> *initializeMap() {
    auto map = new std::map<int, std::string>();

    for (int i = 0; i < 128; ++i) {
        map->insert({i, std::string(1, i)});
    }

    return map;
}

void lzwDecoding(const std::vector<int> &fragments, std::map<int, std::string> *dictionary) {
    std::string string;

    for (int index = 0; index < fragments.size(); ++index) {
        if (fragments.at(index) > dictionary->size()) {
            continue;
        } else {
            if (fragments.at(index) == dictionary->size()) {
                dictionary->operator[](dictionary->size()) = string + string[0];
            } else {
                if (!string.empty()) {
                    dictionary->operator[](dictionary->size()) =
                        string + dictionary->at(fragments[index])[0];
                }
            }
        }

        std::cout << dictionary->at(fragments[index]);
        string = dictionary->at(fragments[index]);
    }
}

std::vector<int> *fillVector(const int amount) {
    auto vector = new std::vector<int>();
    int input_number;

    for (int i = 0; i < amount; ++i) {
        std::cin >> input_number;
        vector->push_back(input_number);
    }

    return vector;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int number_of_fragments;
    std::cin >> number_of_fragments;

    auto vector = fillVector(number_of_fragments);

    auto map = initializeMap();

    lzwDecoding(*vector, map);

    delete map;
    delete vector;
    return 0;
}
