#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <tuple>

int calculateAnswer(std::vector<std::tuple<int, int, double>> *prices_table,
                    std::vector<std::pair<int, int>> *answer, int *sum, int *amount,
                    int max_weight) {
    int max = 0;
    int weight_remainder = max_weight;
    for (size_t i = 0; i < prices_table->size(); ++i) {
        if (std::get<0>(prices_table->at(i)) <= weight_remainder) {
            ++(*amount);
            (*sum) += std::get<1>(prices_table->at(i));
            max += std::get<0>(prices_table->at(i));
            answer->push_back({std::get<0>(prices_table->at(i)), std::get<1>(prices_table->at(i))});
            weight_remainder -= std::get<0>(prices_table->at(i));
        }
    }

    return max;
}

void printAnswer(int max, std::vector<std::pair<int, int>> *answer, int sum, int amount) {
    std::cout << sum << '\n' << max << '\n' << amount << '\n';

    for (size_t i = 0; i < answer->size(); ++i) {
        std::cout << answer->at(i).first << ' ';
    }
    std::cout << '\n';

    for (size_t i = 0; i < answer->size(); ++i) {
        std::cout << answer->at(i).second << ' ';
    }
}

std::vector<std::tuple<int, int, double>> *createData(int amount) {
    auto vector = new std::vector<std::tuple<int, int, double>>(amount);

    int input_data;
    for (int i = 0; i < amount; ++i) {
        std::cin >> input_data;
        vector->at(i) = {input_data, 0, 0};
    }

    for (int i = 0; i < amount; ++i) {
        std::cin >> input_data;
        std::get<1>(vector->at(i)) = input_data;
        std::get<2>(vector->at(i)) = static_cast<double>(input_data) / std::get<0>(vector->at(i));
    }

    return vector;
}

bool mySort(const std::tuple<int, int, double> &a, const std::tuple<int, int, double> &b) {
    return (std::get<2>(a) == std::get<2>(b)) ? (std::get<0>(a) > std::get<0>(b))
                                              : (std::get<2>(a) > std::get<2>(b));
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int number_of_items;
    int max_weight;

    std::cin >> number_of_items >> max_weight;

    auto prices_table = createData(number_of_items);

    std::sort(prices_table->begin(), prices_table->end(), mySort);

    auto answer = new std::vector<std::pair<int, int>>();
    int sum = 0;
    int amount = 0;
    int max = calculateAnswer(prices_table, answer, &sum, &amount, max_weight);

    printAnswer(max, answer, sum, amount);

    delete prices_table;
    delete answer;
    return 0;
}
