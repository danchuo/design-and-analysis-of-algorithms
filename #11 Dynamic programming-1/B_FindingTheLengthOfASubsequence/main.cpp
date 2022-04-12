#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> *createTable(int n, int m) {
    auto table = new std::vector<std::vector<int>>(n);

    for (int i = 0; i < n; ++i) {
        table->at(i) = std::vector<int>(m);
    }

    return table;
}

void assembleLcs(const std::string &first, const std::string &second,
                 std::vector<std::vector<int>> *table, int i, int j, int *answer) {
    if (table->at(i).at(j) == 0) {
        return;
    }

    if (first[i - 1] == second[j - 1]) {
        ++(*answer);
        return assembleLcs(first, second, table, i - 1, j - 1, answer);
    }

    if (table->at(i - 1).at(j) < table->at(i).at(j - 1)) {
        return assembleLcs(first, second, table, i, j - 1, answer);
    }

    return assembleLcs(first, second, table, i - 1, j, answer);
}

void calculateTable(const std::string &first, const std::string &second,
                    std::vector<std::vector<int>> *table) {
    for (int index = 0; index < table->size(); ++index) {
        for (int jj = 0; jj < table->at(0).size(); ++jj) {
            if (jj == 0 || index == 0) {
                continue;
            }

            if (first[index] == second[jj]) {
                table->at(index).at(jj) = table->at(index - 1).at(jj - 1) + 1;
            } else {
                table->at(index).at(jj) =
                    std::max(table->at(index - 1).at(jj), table->at(index).at(jj - 1));
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string first;
    std::string second;

    std::getline(std::cin, first);
    std::getline(std::cin, second);

    auto table = createTable(first.length() + 1, second.length() + 1);

    calculateTable(first, second, table);

    int answer = 0;
    assembleLcs(first, second, table, first.length(), second.length(), &answer);

    std::cout << answer;

    delete table;
    return 0;
}
