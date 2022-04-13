#include <iostream>
#include <algorithm>
#include <vector>

std::vector<int> *fillVector(int amount) {
    std::vector<int> *vector = new std::vector<int>(amount);

    int input_number;

    for (int i = 1; i < amount; ++i) {
        std::cin >> input_number;
        vector->operator[](i) = input_number;
    }
    return vector;
}

std::vector<std::vector<int>> *createTable(int n, int m) {
    auto table = new std::vector<std::vector<int>>(n);

    for (int i = 0; i < n; ++i) {
        table->at(i) = std::vector<int>(m);
    }

    return table;
}

int calculateMinimalPrice(std::vector<int> *peaces, int number_of_cuts) {
    auto table = createTable(number_of_cuts, number_of_cuts);
    for (int j = 1; j < number_of_cuts; ++j) {
        for (int i = j - 2; i > -1; --i) {
            table->at(i).at(j) = INT32_MAX;
            for (int k = i + 1; k <= j; ++k) {
                table->at(i).at(j) =
                    std::min(table->at(i).at(j), table->at(i).at(k) + table->at(k).at(j));
            }
            table->at(i).at(j) += peaces->at(j) - peaces->at(i);
        }
    }

    int answer = table->at(0).at(number_of_cuts - 1);
    delete table;
    return answer;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int length;
    int number_of_cuts;

    std::cin >> length >> number_of_cuts;

    auto vector = fillVector(number_of_cuts + 1);
    vector->push_back(length);

    std::cout << calculateMinimalPrice(vector, number_of_cuts + 2);

    delete vector;
    return 0;
}
