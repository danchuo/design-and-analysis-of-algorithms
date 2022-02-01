#include <iostream>
#include <vector>
#include <algorithm>

int binSearch(std::vector<int32_t> *vector, int32_t key) {
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

//    if (key - vector->at(left) <= vector->at(right) - key) {
//        return left;
//    }

    return right;
}

std::vector<int32_t> *fillVector(int amount, int64_t *sum) {
    std::vector<int32_t> *vector = new std::vector<int32_t>(amount);

    int32_t input_number;

    for (int i = 0; i < amount; ++i) {
        std::cin >> input_number;
        *sum += input_number;
        vector->operator[](i) = input_number;
    }
    return vector;
}

int calculateSegment(std::vector<int32_t> *wires, int64_t length, int segments) {
    int max_segments = 0;

    int start_index = binSearch(wires, length);

    while (max_segments < segments) {
        max_segments += wires->at(start_index) / length;
        ++length;
    }

    return length;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int amount;
    int segments;

    std::cin >> amount;
    std::cin >> segments;

    int64_t sum = 0;
    auto wires = fillVector(amount, &sum);

    int64_t length = sum / segments;
    std::sort(wires->begin(), wires->end());

    if (length == 0) {
        std::cout << 0;
    } else {
        std::cout << calculateSegment(wires, length, segments);
    }

    delete wires;

    return 0;
}
