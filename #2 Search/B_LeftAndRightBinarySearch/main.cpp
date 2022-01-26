#include <iostream>
#include <vector>

std::vector<int32_t> *fillVector(int amount) {
    std::vector<int32_t> *vector = new std::vector<int32_t>(amount);

    int32_t input_number;

    for (int i = 0; i < amount; ++i) {
        std::cin >> input_number;
        vector->operator[](i) = input_number;
    }
    return vector;
}

int32_t binSearchRight(std::vector<int32_t> *vector, int32_t key) {
    int left = -1;
    int right = vector->size();
    int middle;

    while (left < right - 1) {
        middle = left + (right - left) / 2;
        if (vector->at(middle) <= key) {
            left = middle;
        } else {
            right = middle;
        }
    }
    return right;
}

int32_t binSearchLeft(std::vector<int32_t> *vector, int32_t key) {
    int left = -1;
    int right = vector->size();
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

void findFirstAndLastEntry(std::vector<int32_t> *first_vector,
                           std::vector<int32_t> *second_vector) {
    int32_t left;
    int32_t right;

    for (int i = 0; i < second_vector->size(); ++i) {
        left = binSearchLeft(first_vector, second_vector->at(i));
        right = binSearchRight(first_vector, second_vector->at(i));

        if (left == right) {
            std::cout << 0 << '\n';
        } else {
            std::cout << left + 1 << ' ' << right << '\n';
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int numbers_in_first_vector;
    int numbers_in_second_vector;

    std::cin >> numbers_in_first_vector;
    std::cin >> numbers_in_second_vector;

    auto first_vector = fillVector(numbers_in_first_vector);
    auto second_vector = fillVector(numbers_in_second_vector);

    findFirstAndLastEntry(first_vector, second_vector);

    delete first_vector;
    delete second_vector;

    return 0;
}
