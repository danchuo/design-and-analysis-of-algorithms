#include <iostream>
#include <vector>
#include <algorithm>

void printVector(std::vector<int> *vector) {
    for (int i = 0; i < vector->size(); ++i) {
        std::cout << vector->at(i) << ' ';
    }
    std::cout << '\n';
}

void partialPermutation(int n) {
    auto answer = new std::vector<int>(n, 1);
    printVector(answer);
    int sum;
    int current;

    while (answer->size() > 1) {
        sum = answer->at(answer->size() - 1);
        answer->pop_back();
        current = answer->size() - 1;

        while (current > 0 && answer->at(current - 1) == answer->at(current)) {
            sum += answer->at(answer->size() - 1);
            answer->pop_back();
            --current;
        }

        ++answer->at(current);
        --sum;

        for (int i = 0; i < sum; ++i) {
            answer->push_back(1);
        }

        printVector(answer);
    }

    delete answer;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;

    std::cin >> n;

    partialPermutation(n);

    return 0;
}
