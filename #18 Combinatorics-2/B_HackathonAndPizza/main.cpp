#include <iostream>
#include <vector>

void printVector(std::vector<int> *vector) {
    for (size_t i = 0; i < vector->size() - 1; ++i) {
        std::cout << vector->at(i) << ' ';
    }
    std::cout << vector->at(vector->size() - 1);
}

std::vector<int> *findPizza(int students, int types, int number) {
    int position = 0;
    int last = types - 1;
    int current = 1;
    int swap;
    auto answer = new std::vector<int>(types);
    answer->at(0) = students;

    while (current < number) {
        if (position != last) {
            --answer->at(position);
            ++position;
            answer->at(position) = 1;
        } else {
            for (--position; answer->at(position) == 0; --position) {
            }
            --answer->at(position);
            swap = 1 + answer->at(last);
            ++position;
            answer->at(last) = 0;
            answer->at(position) = swap;
        }
        ++current;
    }

    return answer;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int students;
    int types;
    int number;

    std::cin >> students >> types >> number;
    auto answer = findPizza(students, types, number);
    printVector(answer);

    delete answer;
    return 0;
}
