#include <iostream>
#include <string>
#include <vector>

int calculatePossibleK(int number_of_bits, const std::string &bits) {
    int unit_counter = 0;
    int blocks = 0;
    std::vector<int> units(bits.length());

    for (int i = 0; i < bits.length(); ++i) {
        units[i] = unit_counter;

        if (bits[i] == '1') {
            ++unit_counter;
        }
    }

    bool is_length_correct;
    for (int block_length = 1; block_length < number_of_bits; ++block_length) {
        is_length_correct = true;

        for (int inner_index = block_length; inner_index < bits.length();
             inner_index += block_length + 1) {
            if (bits[inner_index] - '0' != units[inner_index] % 2) {
                is_length_correct = false;
                break;
            }
        }

        if (is_length_correct) {
            ++blocks;
        }
    }

    return blocks;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number_of_bits;
    std::string bits;

    std::cin >> number_of_bits;
    std::getline(std::cin, bits);
    std::getline(std::cin, bits);

    std::cout << calculatePossibleK(number_of_bits, bits);

    return 0;
}
