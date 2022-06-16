#include <iostream>
#include <vector>
#include <algorithm>

void printAnswer(std::vector<int> *vector, int m) {
    for (int i = 0; i < m - vector->size(); ++i) {
        std::cout << 1 << ' ';
    }

    for (int i = vector->size() - 1; i > 0; --i) {
        std::cout << vector->at(i) + 1 << ' ';
    }

    std::cout << vector->at(0) + 1;
}

std::vector<int> *toBase(int number, int base) {
    auto answer = new std::vector<int>();

    int i = number ? 0 : 1;
    while (number != 0) {
        answer->push_back(number % base);
        ++i;
        number /= base;
    }

    return answer;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    int m;
    int k;

    std::cin >> n >> m >> k;

    auto answer = toBase(k - 1, n);

    printAnswer(answer, m);

    delete answer;
    return 0;
}
