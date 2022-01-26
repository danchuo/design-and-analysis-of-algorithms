#include <iostream>

void printTwoMax() {
    int first_max = INT16_MIN;
    int second_max = INT16_MIN;

    int input_number;

    std::cin >> input_number;

    while (input_number != 0) {
        if (input_number >= first_max) {
            second_max = first_max;
            first_max = input_number;
        } else {
            if (input_number > second_max) {
                second_max = input_number;
            }
        }

        std::cin >> input_number;
    }

    std::cout << first_max << '\n' << second_max;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    printTwoMax();

    return 0;
}
