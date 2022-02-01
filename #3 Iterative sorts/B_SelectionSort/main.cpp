#include <iostream>
#include <vector>

std::vector<int> *fillVector(int amount) {
    std::vector<int> *vector = new std::vector<int>(amount);

    int input_number;

    for (int i = 0; i < amount; ++i) {
        std::cin >> input_number;
        vector->operator[](i) = input_number;
    }
    return vector;
}

void printVector(std::vector<int> *vector) {
    for (int i = 0; i < vector->size(); ++i) {
        std::cout << vector->at(i) << ' ';
    }
}

int selectionSort(std::vector<int> *vector) {
    int min_index;
    int var_to_swap;
    int swaps = 0;

    for (int index = 0; index < vector->size() - 1; ++index) {
        min_index = index;
        for (int j = index + 1; j < vector->size(); ++j) {
            if (vector->at(j) < vector->at(min_index)) {
                min_index = j;
            }
        }

        if (min_index != index) {
            var_to_swap = vector->at(index);
            vector->at(index) = vector->at(min_index);
            vector->at(min_index) = var_to_swap;
            ++swaps;
        }
    }

    return swaps;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int amount;
    std::cin >> amount;

    auto vector = fillVector(amount);

    int swaps = selectionSort(vector);

    printVector(vector);
    std::cout << '\n' << swaps;

    delete vector;
    return 0;
}
