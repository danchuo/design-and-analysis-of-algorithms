#include <iostream>
#include <vector>
#include <utility>

void printVector(std::vector<int> *vector) {
    for (int i = 0; i < vector->size(); ++i) {
        std::cout << vector->at(i) << ' ';
    }
}

void siftUp(std::vector<int> *vector, int i) {
    while (vector->at(i) < vector->at((i - 1) / 2)) {
        std::swap(vector->at(i), vector->at((i - 1) / 2));
        i = (i - 1) / 2;
    }
}

std::vector<int> *fillVector(int amount) {
    std::vector<int> *vector = new std::vector<int>();

    int input_number;

    for (int i = 0; i < amount; ++i) {
        std::cin >> input_number;
        vector->push_back(input_number);
        if (i != 0) {
            siftUp(vector, i);
        }
    }
    return vector;
}

void siftDown(std::vector<int> *vector, int i) {
    int left, right, j;

    while (2 * i + 1 < vector->size()) {
        left = 2 * i + 1;
        right = 2 * i + 2;
        j = left;
        if (right < vector->size() && vector->at(right) < vector->at(left)) {
            j = right;
        }

        if (vector->at(i) <= vector->at(j)) {
            break;
        }

        std::swap(vector->at(i), vector->at(j));
        i = j;
    }
}

int takeMin(std::vector<int> *vector) {
    int min = vector->at(0);
    if (vector->size() > 1) {
        vector->operator[](0) = vector->at(vector->size() - 1);
        vector->pop_back();
        siftDown(vector, 0);
    }
    return min;
}

std::vector<int> *sortHeap(std::vector<int> *vector) {
    std::vector<int> *sorted = new std::vector<int>();
    int amount = vector->size();

    for (int i = 0; i < amount; ++i) {
        sorted->push_back(takeMin(vector));
    }

    return sorted;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int amount;
    std::cin >> amount;

    auto vector = fillVector(amount);

    auto sorted = sortHeap(vector);

    printVector(sorted);

    delete sorted;
    delete vector;
    return 0;
}
