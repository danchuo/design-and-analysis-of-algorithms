#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "BigIntegerUtils2.h"

void printVector(std::vector<int> *vector) {
    for (int i = 0; i < vector->size() - 1; ++i) {
        std::cout << vector->at(i) << ' ';
    }
    std::cout << vector->at(vector->size() - 1);
}

void getNext(std::vector<int> *vector) {
    int amount = vector->size() - 1;

    int i = amount;
    while (i > 1 && (vector->at(i) < vector->at(i - 1))) {
        --i;
    }

    int j = amount;

    while (vector->at(j) < vector->at(i - 1)) {
        --j;
    }

    std::swap(vector->at(i - 1), vector->at(j));

    int limit = (amount - i + 1) / 2 - 1;
    for (int k = 0; k <= limit; ++k) {
        std::swap(vector->at(i + k), vector->at(amount - k));
    }
}

void getKVariant(BigInteger days, BigInteger number_of_variant) {
    auto current_plan = new std::vector<int>(days.toInt());

    for (size_t i = 0; i < current_plan->size(); ++i) {
        current_plan->at(i) = i + 1;
    }

    BigInteger number_of_current_variant = 1;

    while (number_of_current_variant < number_of_variant) {
        getNext(current_plan);
        ++number_of_current_variant;
    }

    printVector(current_plan);

    delete current_plan;
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

    getKVariant(students, number_of_variant);

    return 0;
}
