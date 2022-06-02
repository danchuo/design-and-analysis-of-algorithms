#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

bool bfs(std::vector<std::vector<int64_t>> *table, int s, int t, std::vector<int64_t> *parents) {
    std::queue<int64_t> queue;
    queue.push(s);
    std::vector<bool> used(table->size());
    used[s] = true;
    parents->at(s) = -1;
    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();
        for (int to = 0; to < table->at(v).size(); ++to) {
            if (!used[to] && table->at(v).at(to) > 0) {
                used[to] = true;
                queue.push(to);
                parents->at(to) = v;
            }
        }
    }

    return used.at(t);
}

int64_t edmondsKarpAlgorithm(std::vector<std::vector<int64_t>> *table, int64_t source, int64_t t) {
    auto parents = new std::vector<int64_t>(table->size());
    int64_t flow = 0;

    while (bfs(table, source, t, parents)) {
        int64_t f = INT64_MAX;
        int64_t s = t;

        while (s != source) {
            f = std::min(f, table->at(parents->at(s)).at(s));
            s = parents->at(s);
        }

        flow += f;

        int64_t v = t;
        while (v != source) {
            int64_t u = parents->at(v);
            table->at(u).at(v) -= f;
            table->at(v).at(u) += f;
            v = parents->at(v);
        }
    }

    delete parents;
    return flow;
}

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

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int64_t vertices;
    int64_t edges;
    std::cin >> vertices >> edges;

    auto table = createTable(vertices, vertices);

    fillTable(table, edges);

    std::cout << edmondsKarpAlgorithm(table, 0, vertices - 1);

    delete table;
    return 0;
}
