#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<int64_t>> *createTable(int n, int m) {
    auto table = new std::vector<std::vector<int64_t>>(n);

    for (int i = 0; i < n; ++i) {
        table->at(i) = std::vector<int64_t>(m);
    }

    return table;
}

void fillTable(std::vector<std::vector<int64_t>> *table, int edges) {
    int64_t first_input_number;
    int64_t second_input_number;
    int64_t third_input_number;

    for (int j = 0; j < edges; ++j) {
        std::cin >> first_input_number >> second_input_number >> third_input_number;
        table->at(first_input_number - 1).at(second_input_number - 1) = third_input_number;
    }
}
int64_t findPath(std::vector<std::vector<int64_t>> *table, std::vector<bool> *vis, int64_t u,
                 int64_t t, int64_t flow) {
    if (u == t) {
        return flow;
    }
    vis->at(u) = true;
    for (int v = 0; v < vis->size(); ++v) {
        if (!vis->at(v) && table->at(u).at(v) > 0) {
            int64_t df = findPath(table, vis, v, t, std::min(flow, table->at(u).at(v)));
            if (df > 0) {
                table->at(u).at(v) -= df;
                table->at(v).at(u) += df;
                return df;
            }
        }
    }

    return 0;
}

int64_t maxFlow(std::vector<std::vector<int64_t>> *table, int64_t source, int64_t t) {
    for (int64_t flow = 0;;) {
        auto vis = new std::vector<bool>(table->size());
        int64_t df = findPath(table, vis, source, t, INT64_MAX);
        if (df == 0) {
            delete vis;
            return flow;
        }
        flow += df;
        delete vis;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int64_t vertices;
    int64_t edges;
    std::cin >> vertices >> edges;

    auto table = createTable(vertices, vertices);

    fillTable(table, edges);

    std::cout << maxFlow(table, 0, vertices - 1);

    delete table;
    return 0;
}
