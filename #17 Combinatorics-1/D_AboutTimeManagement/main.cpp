#include <iostream>
#include <string>
#include <vector>
#include "BigIntegerUtils2.h"

void printVector(std::vector<int> *vector, int limit) {
    for (int i = 0; i < limit; ++i) {
        std::cout << vector->at(i) << ' ';
    }
}

void getNext(std::vector<int> *vector, int n, int m) {
    int k = m;
    for (int i = k - 1; i > -1; --i) {
        if (vector->at(i) < n - k + i + 1) {
            ++(vector->at(i));
            for (int j = i + 1; j < k; ++j) {
                vector->at(j) = vector->at(j - 1) + 1;
            }
            return;
        }
    }
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

    BigInteger cases;
    BigInteger number_of_plan;
    BigInteger tasks;
    std::string input;

    std::cin >> input;
    cases = stringToBigInteger(input);

    std::cin >> input;
    number_of_plan = stringToBigInteger(input);

    std::cin >> input;
    tasks = stringToBigInteger(input);

    getKPlan(cases, tasks, number_of_plan);

    return 0;
}
