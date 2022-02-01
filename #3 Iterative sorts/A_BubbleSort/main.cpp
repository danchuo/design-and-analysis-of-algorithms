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

int bubbleSort(std::vector<int> *vector) {
    int swaps = 0;
    int last_changed_index;
    int bound = vector->size() - 1;
    int var_to_swap;

    for (int index = 0; index < vector->size() - 1; ++index) {
        last_changed_index = 0;

        for (int j = 0; j < bound; ++j) {
            if (vector->at(j) > vector->at(j + 1)) {
                var_to_swap = vector->at(j);
                vector->at(j) = vector->at(j + 1);
                vector->at(j + 1) = var_to_swap;
                last_changed_index = j;
                ++swaps;
            }
        }

        if (last_changed_index == 0) {
            return swaps;
        } else {
            bound = last_changed_index;
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

    int swaps = bubbleSort(vector);

    printVector(vector);
    std::cout << '\n' << swaps;

    delete vector;
    return 0;
}
