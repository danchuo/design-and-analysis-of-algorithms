#include <iostream>
#include <string>
#include <vector>
#include "BigIntegerUtils2.h"

void printVector(std::vector<int> *vector) {
    for (int i = 0; i < vector->size(); ++i) {
        std::cout << vector->at(i) << ' ';
    }
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

int getFirstNotUsed(int index, std::vector<bool> *used) {
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

void findKPlan(BigInteger n, BigInteger m, BigInteger k) {
    auto used = new std::vector<bool>(n.toInt());
    auto current_variant = new std::vector<int>();
    BigInteger amount_of_variants = numberOfVariants(n.toInt(), m.toInt());
    BigInteger current_index = 0;
    BigInteger margin = 0;
    BigInteger possible_transitions;
    BigInteger next_element;

    while (current_variant->size() < m.toInt()) {
        possible_transitions = amount_of_variants / (n - current_index);

        auto index = ((k - margin) / possible_transitions);

        next_element = getFirstNotUsed(index.toInt(), used);

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

    BigInteger shirts;
    BigInteger days;
    BigInteger number_of_plan;
    std::string input;

    std::cin >> input;
    shirts = stringToBigInteger(input);

    std::cin >> input;
    days = stringToBigInteger(input);

    std::cin >> input;
    number_of_plan = stringToBigInteger(input);

    findKPlan(shirts, days, number_of_plan - 1);

    return 0;
}
