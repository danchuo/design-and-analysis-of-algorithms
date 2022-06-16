#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "BigIntegerUtils2.h"

void printAnswer(std::vector<int> *vector, int m) {
    for (int i = 0; i < m - vector->size(); ++i) {
        std::cout << 1 << ' ';
    }

    for (int i = vector->size() - 1; i > 0; --i) {
        std::cout << vector->at(i) + 1 << ' ';
    }
    std::cout << vector->at(0) + 1;
}

std::vector<int> *toBase(BigInteger number, int base) {
    auto answer = new std::vector<int>();

    int i = 0;
    while (number != 0) {
        answer->push_back((number % base).toInt());
        ++i;
        number /= base;
        --base;
    }

    return answer;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    BigInteger k;
    std::string input;

    std::cin >> n;

    std::cin >> input;
    k = stringToBigInteger(input);

    auto answer = toBase(k - 1, n);
    printAnswer(answer, n);
    delete answer;
    return 0;
}
