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

int countZeros(std::vector<int> z_vector) {
    int answer = 1;
    auto max = std::max_element(z_vector.begin(), z_vector.end());

    for (int i = 1; i < static_cast<int>(z_vector.size()); ++i) {
        if (z_vector[i] != (*max)) {
            ++answer;
        } else {
            return answer;
        }
    }

    return answer;
}

std::vector<int> calculateZFunction(const std::string &input_string) {
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

    return z_vector;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string input_string;

    std::getline(std::cin, input_string);
    std::cout << countZeros(calculateZFunction(input_string));

    return 0;
}
