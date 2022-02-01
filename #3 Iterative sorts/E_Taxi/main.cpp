#include <iostream>
#include <vector>
#include <string>
#include <sstream>

// https://ru.stackoverflow.com/a/532827
std::vector<std::string> split(const std::string &s, char key) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> tokens;
    while (std::getline(ss, item, key)) {
        tokens.push_back(item);
    }
    return tokens;
}

std::vector<int> *fillVector() {
    std::vector<int> *vector = new std::vector<int>();

    std::string input_string;

    std::getline(std::cin, input_string);

    int input_number;

    auto strings = split(input_string, ' ');

    for (int i = 0; i < strings.size(); ++i) {
        input_number = std::stoi(strings[i]);
        vector->push_back(input_number);
    }
    return vector;
}

void printVector(std::vector<int> *vector) {
    for (int i = 0; i < vector->size(); ++i) {
        std::cout << vector->at(i) << ' ';
    }
}

void bubbleSort(std::vector<int> *vector) {
    int last_changed_index;
    int bound = vector->size() - 1;
    int var_to_swap;

    for (int index = 0; index < vector->size() - 1; ++index) {
        last_changed_index = 0;

        for (int j = 0; j < bound; ++j) {
            if (vector->at(j) > vector->at(j + 1)) {
                var_to_swap = vector->at(j);
                vector->at(j) = vector->at(j + 1);
                vector->at(j + 1) = var_to_swap;
                last_changed_index = j;
            }
        }

        if (last_changed_index == 0) {
            return;
        } else {
            bound = last_changed_index;
        }
    }
}

void bubbleSortDecreasing(std::vector<int> *vector) {
    int last_changed_index;
    int bound = vector->size() - 1;
    int var_to_swap;

    for (int index = 0; index < vector->size() - 1; ++index) {
        last_changed_index = 0;

        for (int j = 0; j < bound; ++j) {
            if (vector->at(j) < vector->at(j + 1)) {
                var_to_swap = vector->at(j);
                vector->at(j) = vector->at(j + 1);
                vector->at(j + 1) = var_to_swap;
                last_changed_index = j;
            }
        }

        if (last_changed_index == 0) {
            return;
        } else {
            bound = last_changed_index;
        }
    }
}

int calculateSum(std::vector<int> *distances, std::vector<int> *prices) {
    int sum = 0;

    for (int i = 0; i < distances->size(); ++i) {
        sum += distances->at(i) * prices->at(i);
    }
    return sum;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto distances = fillVector();
    auto prices = fillVector();

    bubbleSort(distances);
    bubbleSortDecreasing(prices);

    std::cout << calculateSum(distances, prices);

    delete distances;
    delete prices;
    return 0;
}
