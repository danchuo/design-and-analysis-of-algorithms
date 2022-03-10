#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void printVector(std::vector<int> vector) {
    int length = static_cast<int>(vector.size());

    for (int i = 0; i < length; ++i) {
        std::cout << vector.at(i) << ' ';
    }
}

void calculatePrefixFunction(std::vector<int> z_vector) {
    std::vector<int> prefix_vector(z_vector.size());
    int length = static_cast<int>(z_vector.size());

    for (int i = 1; i < length; ++i) {
        if (z_vector[i] != 0) {
            for (int j = z_vector[i] - 1; j >= 0 && !(prefix_vector[i + j]); --j) {
                prefix_vector[i + j] = j + 1;
            }
        }
    }

    printVector(prefix_vector);
}

void calculateZFunction(const std::string &input_string) {
    std::vector<int> z_vector(input_string.length());
    int length = static_cast<int>(input_string.length());
    int left_index = 0;
    int right_index = 0;

    for (int i = 1; i < length; ++i) {
        z_vector[i] = std::max(0, std::min(right_index - i + 1, z_vector[i - left_index]));
        while ((i + z_vector[i] < length) &&
               (input_string[i + z_vector[i]] == input_string[z_vector[i]])) {
            ++z_vector[i];
        }
        if (i + z_vector[i] > right_index) {
            left_index = i;
            right_index = i + z_vector[i] - 1;
        }
    }

    calculatePrefixFunction(z_vector);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string input_string;

    std::getline(std::cin, input_string);

    calculateZFunction(input_string);

    return 0;
}
