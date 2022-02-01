#include <iostream>
#include <vector>
#include <utility>

std::vector<int> *insertionSort(int amount, int *swaps) {
    std::vector<int> *vector = new std::vector<int>();
    int input_number;
    bool is_moved;
    std::cin >> input_number;
    vector->push_back(input_number);

    for (int index = 1; index < amount; ++index) {
        std::cin >> input_number;
        is_moved = false;
        vector->push_back(input_number);

        for (int j = vector->size() - 2; j > -1; --j) {
            if (input_number < vector->at(j)) {
                std::swap((vector->at(j)), (vector->at(j + 1)));
                is_moved = true;
            } else {
                if (!is_moved) {
                    ++(*swaps);
                }
                break;
            }
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

    auto vector = insertionSort(amount, &swaps);

    printVector(vector);
    std::cout << '\n' << swaps;

    delete vector;
    return 0;
}
