#include <iostream>
#include <string>
#include <vector>

int calculateMinimumNumberOfCrossing(const std::string &symbols) {
    int n = symbols.length();

    std::vector<int> left_coast(n + 1);
    std::vector<int> right_coast(n + 1);
    std::vector<int> previous_left_coast(n + 1);
    std::vector<int> previous_right_coast(n + 1);
    right_coast[0] = 1;

    for (int index = 1; index <= n; ++index) {
        left_coast[index] = left_coast[index - 1];
        right_coast[index] = right_coast[index - 1];
        previous_left_coast[index] = previous_left_coast[index - 1];
        previous_right_coast[index] = previous_right_coast[index - 1];

        if (symbols[index - 1] == 'L') {
            left_coast[index] = left_coast[previous_left_coast[index - 1]] + 1;
            previous_left_coast[index] = index;
        } else if (symbols[index - 1] == 'R') {
            right_coast[index] = right_coast[previous_right_coast[index - 1]] + 1;
            previous_right_coast[index] = index;
        } else {
            left_coast[index] = left_coast[previous_left_coast[index - 1]] + 1;
            right_coast[index] = right_coast[previous_right_coast[index - 1]] + 1;
            previous_left_coast[index] = previous_right_coast[index] = index;
        }

        if (left_coast[index - 1] == 0) {
            left_coast[index] = 1;
        }

        if (right_coast[index - 1] == 1) {
            right_coast[index] = 2;
        }

        if (left_coast[index] + 1 < right_coast[index]) {
            right_coast[index] = left_coast[index] + 1;
        }

        if (right_coast[index] + 1 < left_coast[index]) {
            left_coast[index] = right_coast[index] + 1;
        }
    }

    return right_coast[n];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string symbols;

    std::getline(std::cin, symbols);

    std::cout << calculateMinimumNumberOfCrossing(symbols);

    return 0;
}
