#include <iostream>
#include <vector>
#include <string>
#include <cmath>

void printVector(std::vector<char> *vector) {
    for (int i = 0; i < vector->size(); ++i) {
        std::cout << vector->at(i);
    }
}

std::vector<char> *calculateControlBits(std::vector<char> *bits) {
    int pow_of_two = 0;
    int unit_counter;
    for (int i = 0; i < bits->size(); i = std::pow(2, pow_of_two) - 1) {
        unit_counter = 0;
        for (int j = i + 2; j <= bits->size(); ++j) {
            if (j & (1 << pow_of_two)) {
                if (bits->operator[](j - 1) == '1') {
                    ++unit_counter;
                }
            }
        }

        if (unit_counter % 2 == 0) {
            bits->operator[](i) = '0';
        } else {
            bits->operator[](i) = '1';
        }

        ++pow_of_two;
    }

    return bits;
}

std::vector<char> *addControlBits(const std::string &string_to_encode) {
    auto answer = new std::vector<char>();
    int pow_of_two = 0;
    int symbols_from_string = 0;
    int index = 0;

    while (5) {
        if (pow(2, pow_of_two) == index + 1) {
            answer->push_back('!');
            ++pow_of_two;
        } else {
            answer->push_back(string_to_encode[symbols_from_string]);
            ++symbols_from_string;
            if (symbols_from_string == string_to_encode.length()) {
                break;
            }
        }
        ++index;
    }

    return answer;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string input_line;
    std::getline(std::cin, input_line);

    auto vector = addControlBits(input_line);
    calculateControlBits(vector);
    printVector(vector);

    delete vector;
    return 0;
}
