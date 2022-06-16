#include <iostream>
#include <vector>
#include <algorithm>

void printVector(std::vector<int> *vector, int limit) {
    for (int i = 0; i < limit; ++i) {
        std::cout << vector->at(i) << ' ';
    }
    std::cout << '\n';
}

void partialPermutation(std::vector<int> *answer, int position, int max, int length) {
    if (length == 0) {
        printVector(answer, position);
    } else {
        for (int i = 1; i <= std::min(max, length); ++i) {
            answer->at(position) = i;
            partialPermutation(answer, position + 1, i, length - i);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;

    std::cin >> n;

    std::vector<int> answer(n);

    partialPermutation(&answer, 0, n, n);

    return 0;
}
