#include <iostream>
#include <vector>

std::vector<std::vector<int>> *createTable(int n, int m, int init_value) {
    auto table = new std::vector<std::vector<int>>(n);

    for (int i = 0; i < n; ++i) {
        table->at(i) = std::vector<int>(m, init_value);
    }

    return table;
}

int calculateWaysRec(std::vector<std::vector<int>> *table, int i, int j) {
    if (i > -1 && j > -1 && i < table->size() && j < table->at(0).size()) {
        if (table->at(i).at(j) != -1) {
            return table->at(i).at(j);
        } else {
            table->at(i).at(j) =
                calculateWaysRec(table, i - 2, j - 1) + calculateWaysRec(table, i - 2, j + 1) +
                calculateWaysRec(table, i - 1, j - 2) + calculateWaysRec(table, i + 1, j - 2);
            return table->at(i).at(j);
        }
    }

    return 0;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int length;
    int width;

    std::cin >> length >> width;

    auto table = createTable(length, width, -1);

    table->at(0).at(0) = 1;

    calculateWaysRec(table, length - 1, width - 1);

    std::cout << (table->at(length - 1).at(width - 1));

    delete table;
    return 0;
}
