#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

std::vector<int> *fillVector(int amount) {
    std::vector<int> *vector = new std::vector<int>(amount);

    int input_number;

    for (int i = 0; i < amount; ++i) {
        std::cin >> input_number;
        vector->operator[](i) = input_number;
    }
    return vector;
}

std::vector<std::vector<int>> *createTable(int n, int m, int init_value) {
    auto table = new std::vector<std::vector<int>>(n);
    for (int i = 0; i < n; ++i) {
        table->at(i) = std::vector<int>(m, init_value);
    }
    return table;
}

void calculateAnswer(std::vector<std::vector<int> *> *prices_table,
                     std::vector<std::vector<int>> *table, std::vector<std::pair<int, int>> *answer,
                     int *sum, int *amount, int i, int j) {
    if (table->at(i).at(j) == 0) {
        return;
    }
    if (table->at(i).at(j) == table->at(i - 1).at(j)) {
        calculateAnswer(prices_table, table, answer, sum, amount, i - 1, j);
    } else {
        calculateAnswer(prices_table, table, answer, sum, amount, i - 1,
                        j - prices_table->at(0)->at(i - 1));
        answer->push_back({prices_table->at(0)->at(i - 1), prices_table->at(1)->at(i - 1)});
        ++(*amount);
        (*sum) += prices_table->at(0)->at(i - 1);
    }
}

void fillTable(std::vector<std::vector<int>> *table,
               std::vector<std::vector<int> *> *prices_table) {
    for (size_t index = 0; index < table->size(); ++index) {
        for (size_t weight = 0; weight < table->at(0).size(); ++weight) {
            if (index == 0 || weight == 0) {
                table->at(index).at(weight) = 0;
                continue;
            }

            if (prices_table->at(0)->at(index - 1) <= weight) {
                table->at(index).at(weight) =
                    std::max(table->at(index - 1).at(weight),
                             table->at(index - 1).at(weight - prices_table->at(0)->at(index - 1)) +
                                 prices_table->at(1)->at(index - 1));
            } else {
                table->at(index).at(weight) = table->at(index - 1).at(weight);
            }
        }
    }
}

void printAnswer(int max, std::vector<std::pair<int, int>> *answer, int sum, int amount) {
    std::cout << max << '\n' << sum << '\n' << amount << '\n';

    for (size_t i = 0; i < answer->size(); ++i) {
        std::cout << answer->at(i).first << ' ';
    }
    std::cout << '\n';

    for (size_t i = 0; i < answer->size(); ++i) {
        std::cout << answer->at(i).second << ' ';
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int number_of_items;
    int max_weight;

    std::cin >> number_of_items >> max_weight;

    auto prices_table = new std::vector<std::vector<int> *>(2);
    prices_table->at(0) = fillVector(number_of_items);
    prices_table->at(1) = fillVector(number_of_items);

    auto table = createTable(number_of_items + 1, max_weight + 1, -1);

    fillTable(table, prices_table);

    auto answer = new std::vector<std::pair<int, int>>();
    int sum = 0;
    int amount = 0;

    calculateAnswer(prices_table, table, answer, &sum, &amount, number_of_items, max_weight);

    printAnswer(table->at(number_of_items).at(max_weight), answer, sum, amount);

    delete prices_table->at(0);
    delete prices_table->at(1);
    delete prices_table;
    delete table;
    delete answer;
    return 0;
}
