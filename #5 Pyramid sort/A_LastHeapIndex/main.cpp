#include <iostream>
#include <vector>

int findLastHeapIndex(int amount) {
    std::vector<int> vector;
    int i = 0;
    int input_number;

    for (i = 0; i < amount; ++i) {
        std::cin >> input_number;
        vector.push_back(input_number);

        if (i > 0 &&
            (input_number > vector.at((i - 1) / 2) || input_number > vector.at((i - 2) / 2))) {
            return i - 1;
        }
    }

    return i - 1;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int amount;
    std::cin >> amount;

    std::cout << findLastHeapIndex(amount);

    return 0;
}
