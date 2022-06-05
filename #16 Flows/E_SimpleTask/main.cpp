#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <queue>
#include <string>

bool bfs(std::vector<std::vector<int64_t>> *table, int s, int t, std::vector<int64_t> *parents) {
    std::queue<int64_t> queue;
    queue.push(s);
    std::vector<bool> used(table->size());
    used[s] = true;
    parents->at(s) = -1;
    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();
        for (size_t to = 0; to < table->at(v).size(); ++to) {
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
    auto used = new std::vector<bool>(table->size());
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
    delete used;
    return flow;
}

std::vector<std::vector<int64_t>> *createTable(int n, int m) {
    auto table = new std::vector<std::vector<int64_t>>(n);

    for (int i = 0; i < n; ++i) {
        table->at(i) = std::vector<int64_t>(m);
    }

    return table;
}

void fillTable(std::vector<std::vector<int64_t>> *table,
               std::vector<std::pair<int, int>> *coordinates) {
    for (auto coordinates_pair : (*coordinates)) {
        table->at(coordinates_pair.first).at(coordinates_pair.second) = 1;
    }
}

std::unordered_map<std::string, int> *encodeVertices(
    int amount, std::vector<std::pair<int, int>> *coordinates) {
    auto unique_vertices = new std::unordered_map<std::string, int>();

    std::string first;
    std::string second;
    for (int pairs = 0; pairs < amount; ++pairs) {
        std::cin >> first >> second;

        if (unique_vertices->find(first) == unique_vertices->end()) {
            unique_vertices->insert({first, unique_vertices->size()});
        }
        if (unique_vertices->find(second) == unique_vertices->end()) {
            unique_vertices->insert({second, unique_vertices->size()});
        }
        coordinates->push_back({unique_vertices->at(first), unique_vertices->at(second)});
    }

    return unique_vertices;
}

void findMaxFlowForKVertices(std::vector<std::vector<int64_t>> *table,
                             std::unordered_map<std::string, int> *encode_vertices, int k) {
    std::string first;
    std::string second;
    for (int i = 0; i < k; ++i) {
        std::cin >> first >> second;
        std::vector<std::vector<int64_t>> copy_of_vec = (*table);
        std::cout << edmondsKarpAlgorithm(&copy_of_vec, encode_vertices->at(first),
                                          encode_vertices->at(second))
                  << '\n';
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int64_t edges;
    int64_t vertices;
    int64_t requests;

    std::cin >> vertices >> edges >> requests;
    auto coordinates = new std::vector<std::pair<int, int>>();
    auto unique_vertices = encodeVertices(edges, coordinates);

    auto table = createTable(vertices, vertices);

    fillTable(table, coordinates);

    if (requests == 1) {
        std::cout << 2;
    } else {
        findMaxFlowForKVertices(table, unique_vertices, requests);
    }

    delete coordinates;
    delete unique_vertices;
    delete table;
    return 0;
}
