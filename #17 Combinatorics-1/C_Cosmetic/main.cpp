#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "BigIntegerUtils2.h"

void printVector(std::vector<int> *vector) {
    for (size_t i = 0; i < vector->size() - 1; ++i) {
        std::cout << vector->at(i) << ' ';
    }
    std::cout << vector->at(vector->size() - 1);
}

BigInteger factorial(int n) {
    BigInteger answer = 1;

    for (int i = 2; i <= n; ++i) {
        answer.multiply(answer, i);
    }

    return answer;
}

BigInteger numberOfVariants(int n, int k) {
    return factorial(n) / (factorial(n - k));
}

int ivanFunction(int index, std::vector<bool> *used) {
    int current_index = 0;
    for (int i = 0; i < used->size(); ++i) {
        if (!used->at(i)) {
            if (current_index == index) {
                used->at(i) = true;
                return i;
            } else {
                ++current_index;
            }
        }
    }
    return 0;
}

void ivanMethod(BigInteger n, BigInteger k) {
    auto used = new std::vector<bool>(n.toInt());
    auto current_variant = new std::vector<int>();
    BigInteger amount_of_variants = numberOfVariants(n.toInt(), n.toInt());
    BigInteger current_index = 0;
    BigInteger margin = 0;
    BigInteger possible_transitions;
    BigInteger next_element;

    while (current_variant->size() < n.toInt()) {
        possible_transitions = amount_of_variants / (n - current_index);

        auto index = ((k - margin) / possible_transitions);

        next_element = ivanFunction(index.toInt(), used);

        current_variant->push_back(next_element.toInt() + 1);

        margin += index * possible_transitions;

        amount_of_variants /= n - current_index;
        ++current_index;
    }

    printVector(current_variant);

    delete used;
    delete current_variant;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    BigInteger students;
    BigInteger number_of_variant;
    std::string input;

    std::cin >> input;
    students = stringToBigInteger(input);

    std::cin >> input;
    number_of_variant = stringToBigInteger(input);

    ivanMethod(students, number_of_variant - 1);

    return 0;
}
