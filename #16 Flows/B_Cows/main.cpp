#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <queue>

inline void hashCombine(std::size_t *seed) {
}

template <typename T, typename... Rest>
inline void hashCombine(std::size_t *seed, const T &v, Rest... rest) {
    std::hash<T> hash;
    (*seed) ^= hash(v) + 0x9e3779b9 + ((*seed) << 6) + ((*seed) >> 2);
    hashCombine(seed, rest...);
}

struct PairHash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        std::size_t h = 0;

        hashCombine(&h, h1, h2);
        return h;
    }
};

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

void fillTable(
    std::vector<std::vector<int64_t>> *table,
    std::vector<std::pair<std::pair<int64_t, int64_t>, std::pair<int64_t, int64_t>>> *coordinates,
    std::unordered_map<std::pair<int64_t, int64_t>, int, PairHash> *unique_vertices) {
    for (auto coordinates_pair : (*coordinates)) {
        table->at(unique_vertices->at(coordinates_pair.first))
            .at(unique_vertices->at(coordinates_pair.second)) = 1;
    }
}

std::unordered_map<std::pair<int64_t, int64_t>, int, PairHash> *encodeVertices(
    int amount, int64_t *s, int64_t *t,
    std::vector<std::pair<std::pair<int64_t, int64_t>, std::pair<int64_t, int64_t>>> *coordinates) {
    auto unique_vertices = new std::unordered_map<std::pair<int64_t, int64_t>, int, PairHash>();

    int64_t first;
    int64_t second;
    int64_t third;
    int64_t fourth;
    for (int pairs = 0; pairs < amount + 1; ++pairs) {
        std::cin >> first >> second >> third >> fourth;

        if (pairs != amount) {
            coordinates->push_back({{first, second}, {third, fourth}});
        }

        if (unique_vertices->find({first, second}) == unique_vertices->end()) {
            unique_vertices->insert({{first, second}, unique_vertices->size()});
        }

        if (unique_vertices->find({third, fourth}) == unique_vertices->end()) {
            unique_vertices->insert({{third, fourth}, unique_vertices->size()});
        }

        if (pairs == amount) {
            int64_t ss = unique_vertices->at({first, second});
            int64_t tt = unique_vertices->at({third, fourth});
            (*s) = ss;
            (*t) = tt;
        }
    }

    return unique_vertices;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int64_t edges;
    int64_t s = 0;
    int64_t t = 0;
    std::cin >> edges;
    auto coordinates =
        new std::vector<std::pair<std::pair<int64_t, int64_t>, std::pair<int64_t, int64_t>>>();
    auto unique_vertices = encodeVertices(edges, &s, &t, coordinates);
    int64_t vertices = unique_vertices->size();

    auto table = createTable(vertices, vertices);

    fillTable(table, coordinates, unique_vertices);

    std::cout << edmondsKarpAlgorithm(table, 0, vertices - 1);

    delete unique_vertices;
    delete coordinates;
    delete table;
    return 0;
}
