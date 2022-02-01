#include <iostream>
#include <vector>
#include <utility>

int binSearchLeft(std::vector<int> *vector, int key, int start_index, int end_index) {
    int left = start_index - 1;
    int right = end_index + 1;
    int middle;

    while (left < right - 1) {
        middle = left + (right - left) / 2;
        if (vector->at(middle) < key) {
            left = middle;
        } else {
            right = middle;
        }
    }
    return right;
}

std::vector<int> *insertionBinarySort(int amount, int *swaps) {
    std::vector<int> *vector = new std::vector<int>();
    int input_number;
    bool is_moved;
    std::cin >> input_number;
    vector->push_back(input_number);

    for (int index = 1; index < amount; ++index) {
        std::cin >> input_number;

        int j = index - 1;
        int key = binSearchLeft(vector, input_number, 0, j);

        vector->push_back(input_number);
        for (int m = j; m > key - 1; --m) {
            std::swap((vector->at(m)), (vector->at(m + 1)));
            ++(*swaps);
        }
    }

    return vector;
}

void printVector(std::vector<int> *vector) {
    for (int i = 0; i < vector->size(); ++i) {
        std::cout << vector->at(i) << ' ';
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int amount;
    int swaps = 0;
    std::cin >> amount;

    if (amount == 0) {
        std::cout << '\n' << 0;
        return 0;
    }

    auto vector = insertionBinarySort(amount, &swaps);

    printVector(vector);
    std::cout << '\n' << swaps;

    delete vector;
    return 0;
}
