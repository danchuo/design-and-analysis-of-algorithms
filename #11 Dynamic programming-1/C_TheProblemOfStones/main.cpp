#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> *fillVector(int amount) {
    std::vector<int> *vector = new std::vector<int>(amount + 1);

    int input_number;

    for (int i = 1; i <= amount; ++i) {
        std::cin >> input_number;
        vector->operator[](i) = input_number;
    }
    return vector;
}

void printVector(std::vector<int> *vector) {
    for (int i = 1; i < vector->size(); ++i) {
        std::cout << vector->at(i) << ' ';
    }
}

std::vector<std::vector<int>> *createTable(int n, int m) {
    auto table = new std::vector<std::vector<int>>(n);

    for (int i = 0; i < n; ++i) {
        table->at(i) = std::vector<int>(m);
    }

    return table;
}

void way(std::vector<int> *answer, int i, int j, std::vector<int> *stones,
         std::vector<std::vector<int>> *table) {
    if (table->at(i)[j] == 0) {
        return;
    }

    if (table->at(i)[j] != table->at(i - 1)[j]) {
        way(answer, i - 1, j - stones->at(i), stones, table);
        answer->at(0) += stones->at(i);
        answer->push_back(stones->at(i));
    } else {
        way(answer, i - 1, j, stones, table);
    }
}

void calculateTable(std::vector<int> *stones, std::vector<std::vector<int>> *table) {
    for (int index = 0; index < table->size(); ++index) {
        for (int jj = 0; jj < table->at(0).size(); ++jj) {
            if (jj == 0 || index == 0) {
                continue;
            }

            if (stones->at(index) > jj) {
                table->at(index).at(jj) = table->at(index - 1).at(jj);
            } else {
                table->at(index).at(jj) =
                    std::max(table->at(index - 1).at(jj),
                             table->at(index - 1).at(jj - stones->at(index)) + stones->at(index));
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int available_stones;
    int max_weight;

    std::cin >> available_stones >> max_weight;

    auto stones = fillVector(available_stones);
    auto table = createTable(available_stones + 1, max_weight + 1);
    auto *answer = new std::vector<int>(1);

    calculateTable(stones, table);
    way(answer, available_stones, max_weight, stones, table);

    std::cout << answer->at(0) << '\n' << answer->size() - 1 << '\n';
    printVector(answer);

    delete stones;
    delete answer;
    delete table;
    return 0;
}
