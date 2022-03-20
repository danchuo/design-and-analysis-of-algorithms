#include <iostream>
#include <string>
#include <cmath>

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

int findPositionWithMistake(const std::string &string) {
    int mistake = 0;

    for (int i = 0; i < string.length(); ++i) {
        if (string[i] == '1') {
            mistake ^= i + 1;
        }
    }

    return mistake;
}

void fixMistake(std::string *string_to_decode) {
    int index_of_mistake = findPositionWithMistake(*string_to_decode);

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

    fixMistake(&input_line);
    printStringWithoutControlBits(input_line);

    return 0;
}
