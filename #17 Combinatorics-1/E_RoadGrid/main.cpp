#include <iostream>
#include "BigIntegerUtils2.h"

BigInteger factorial(int n) {
    BigInteger answer = stringToBigInteger("1");

    for (int i = 2; i <= n; ++i) {
        answer.multiply(answer, i);
    }

    return answer;
}

BigInteger numberOfCombinations(int n, int k) {
    BigInteger answer = stringToBigInteger("1");

    answer = factorial(n) / (factorial(n - k) * factorial(k));

    return answer;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int x;
    int y;
    std::cin >> x >> y;

    BigInteger first = x + y;
    BigInteger second = x;

    std::cout << numberOfCombinations(first.toInt(), second.toInt()) << '\n';

    return 0;
}
