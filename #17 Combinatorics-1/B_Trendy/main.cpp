#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "BigIntegerUtils2.h"

void printVector(std::vector<int> *vector, int limit) {
    for (int i = 0; i < limit; ++i) {
        std::cout << vector->at(i) << ' ';
    }
}

void getNext(std::vector<int> *vector, int n, int m) {
    int j;
    int k;
    int left;
    int right;
    do {
        j = n - 2;
        while (j != -1 && vector->at(j) >= vector->at(j + 1)) {
            --j;
        }
        k = n - 1;
        while (vector->at(j) >= vector->at(k)) {
            --k;
        }

        std::swap(vector->at(j), vector->at(k));
        left = j + 1;
        right = n - 1;
        while (left < right) {
            std::swap(vector->at(left++), vector->at(right--));
        }
    } while (j > m - 1);
}

void getKPlan(BigInteger shirts, const BigInteger days, const BigInteger number_of_plan) {
    auto current_plan = new std::vector<int>(shirts.toInt());

    for (size_t i = 0; i < current_plan->size(); ++i) {
        current_plan->at(i) = i + 1;
    }

    BigInteger number_of_current_plan = 1;

    while (number_of_current_plan < number_of_plan) {
        getNext(current_plan, shirts.toInt(), days.toInt());

        ++number_of_current_plan;
    }

    printVector(current_plan, days.toInt());

    delete current_plan;
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

    getKPlan(shirts, days, number_of_plan);

    return 0;
}
