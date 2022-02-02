#include <iostream>
#include <vector>
#include <string>
#include <sstream>

// https://ru.stackoverflow.com/a/532827
std::vector<int> *split(const std::string &s, char key) {
    std::stringstream ss(s);
    std::string item;
    std::vector<int> *tokens = new std::vector<int>();
    while (std::getline(ss, item, key)) {
        tokens->push_back(std::stoi(item));
    }
    return tokens;
}

std::vector<int> *fillVector() {
    std::string input_string;

    std::getline(std::cin, input_string);

    auto strings = split(input_string, ' ');

    return strings;
}

void bubbleSort(std::vector<int> *increasing_vector, std::vector<int> *decreasing_vector) {
    for (int index = 0; index < increasing_vector->size() - 1; ++index) {
        for (int inner_index = 0; inner_index < increasing_vector->size() - index - 1;
             ++inner_index) {
            if (increasing_vector->at(inner_index) > increasing_vector->at(inner_index + 1)) {
                int temp_variable = increasing_vector->at(inner_index);
                increasing_vector->at(inner_index) = increasing_vector->at(inner_index + 1);
                increasing_vector->at(inner_index + 1) = temp_variable;
            }

            if (decreasing_vector->at(inner_index) < decreasing_vector->at(inner_index + 1)) {
                int temp_variable = decreasing_vector->at(inner_index);
                decreasing_vector->at(inner_index) = decreasing_vector->at(inner_index + 1);
                decreasing_vector->at(inner_index + 1) = temp_variable;
            }
        }
    }
}

int64_t calculateSum(std::vector<int> *distances, std::vector<int> *prices) {
    int64_t sum = 0;

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

    bubbleSort(distances, prices);

    std::cout << calculateSum(distances, prices);

    delete distances;
    delete prices;
    return 0;
}
