#include <iostream>
#include <string>

int calculatePossibleK(int number_of_bits, const std::string &bits) {
    int unit_counter;
    int blocks = 0;

    for (int block_length = 1; block_length < number_of_bits; ++block_length) {
        unit_counter = 0;

        for (int inner_index = 0; inner_index < bits.length(); ++inner_index) {
            if (((inner_index % block_length) != 0) || (inner_index == 0)) {
                if (bits[inner_index] == '1') {
                    ++unit_counter;
                }
            } else {
                if (unit_counter % 2 != bits[inner_index] - '0') {
                    break;
                } else {
                    if (bits.length() - inner_index <= block_length + 1) {
                        ++blocks;
                    }
                }
            }
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
