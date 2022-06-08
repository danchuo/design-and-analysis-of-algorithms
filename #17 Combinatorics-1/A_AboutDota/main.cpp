#include <iostream>
#include <string>
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

BigInteger oddFactorial(int n) {
    BigInteger answer = stringToBigInteger("1");

    for (int i = 3; i <= n; i += 2) {
        answer.multiply(answer, i);
    }

    return answer;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    BigInteger students;
    BigInteger places;
    std::string input;

    std::cin >> input;
    students = stringToBigInteger(input);

    std::cin >> input;
    places = stringToBigInteger(input);

    std::cout << factorial(students.toInt()) << '\n';
    std::cout << numberOfCombinations(students.toInt(), places.toInt()) << '\n';
    std::cout << oddFactorial(students.toInt()) << '\n';

    return 0;
}
