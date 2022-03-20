#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

std::string *calculateControlBits(std::string *bits) {
    auto control_bits = new std::string();
    int pow_of_two = 0;
    int unit_counter;
    for (int i = 0; i < bits->size(); i = std::pow(2, pow_of_two) - 1) {
        unit_counter = (bits->at(i) == '1') ? 1 : 0;
        for (int j = i + 2; j <= bits->size(); ++j) {
            if (j & (1 << pow_of_two)) {
                if (bits->operator[](j - 1) == '1') {
                    ++unit_counter;
                }
            }
        }

        if (unit_counter % 2 == 0) {
            control_bits->push_back('0');
        } else {
            control_bits->push_back('1');
        }

        ++pow_of_two;
    }

    return control_bits;
}

void printStringWithoutControlBits(const std::string &string) {
    int pow_of_two = 0;
    for (int i = 0; i < string.length(); ++i) {
        if (i == std::pow(2, pow_of_two) - 1) {
            ++pow_of_two;
        } else {
            std::cout << string[i];
        }
    }
}

void fixMistake(std::string *string_to_decode, const std::string control_bits) {
    int index_of_mistake =
        std::stoi(std::string(control_bits.rbegin(), control_bits.rend()), nullptr, 2);

    if (index_of_mistake != 0) {
        string_to_decode->operator[](index_of_mistake - 1) =
            (string_to_decode->at(index_of_mistake - 1) == '1') ? '0' : '1';
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string input_line;
    std::getline(std::cin, input_line);

    std::string *control_bits;

    control_bits = calculateControlBits(&input_line);
    try {
        fixMistake(&input_line, *control_bits);
    } catch (...) {
    }

    printStringWithoutControlBits(input_line);

    delete control_bits;
    return 0;
}
