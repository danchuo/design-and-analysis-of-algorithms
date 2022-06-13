#include <math.h>
#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <stack>
#include <limits>

double calculateDistance(const std::pair<int, int> &x, const std::pair<int, int> &y) {
    return sqrt(pow(x.first - y.first, 2) +
        pow(x.second - y.second, 2));
}

std::vector<std::vector<double>> *createSquareTable(int n) {
    auto table = new std::vector<std::vector<double>>(n);
    for (int i = 0; i < n; ++i) {
        table->at(i) = std::vector<double>(n);
    }
    return table;
}

int getMinIndex(std::vector<int> *key, std::vector<bool> *mst, int n) {
    int min = INT32_MAX;
    int min_index;

    for (int i = 0; i < n; ++i) {
        if (!mst->at(i) && key->at(i) < min) {
            min = key->at(i);
            min_index = i;
        }
    }

    return min_index;
}

void createHamiltonianPath(std::vector<int> *path, double *path_cost, std::vector<std::vector<double>> *graph) {
    int n = graph->size();
    auto visited = new std::vector<bool>(n);

    (*path_cost) = 0;

    int root = path->front();
    std::vector<int>::iterator current = path->begin();
    std::vector<int>::iterator next = path->begin() + 1;
    visited->at(root) = true;

    while (next != path->end()) {
        if (!visited->at(*next)) {
            (*path_cost) += graph->at(*current).at(*next);
            current = next;
            visited->at(*current) = 1;
            next = current + 1;
        } else {
            next = path->erase(next);
        }
    }

    if (next != path->end()) {
        (*path_cost) += graph->at(*current).at(*next);
    }

    delete visited;
}

void eulerTourAlgorithm(int start, std::vector<int> *path, std::vector<std::vector<double>> *mst) {
    auto mst_copy = new std::vector<std::vector<double>>(mst->size());
    for (int i = 0; i < mst->size(); ++i) {
        mst_copy->at(i) = std::vector<double>();
        for (int j = 0; j < mst->at(i).size(); ++j) {
            mst_copy->at(i).push_back(mst->at(i).at(j));
        }
    }

    std::stack<int> stack;
    int position = start;
    path->push_back(start);
    while (!stack.empty() || !mst_copy->at(position).empty()) {
        if (mst_copy->at(position).empty()) {
            path->push_back(position);
            position = stack.top();
            stack.pop();
        } else {
            stack.push(position);
            int neighbor = mst_copy->at(position).back();
            mst_copy->at(position).pop_back();
            for (int i = 0; i < mst_copy->at(neighbor).size(); ++i) {
                if (mst_copy->at(neighbor).at(i) == position) {
                    mst_copy->at(neighbor).erase(mst_copy->at(neighbor).begin() + i);
                }
            }
            position = neighbor;
        }
    }
    path->push_back(position);
    delete mst_copy;
}

double findBestPath(int start, std::vector<std::vector<double>> *mst, std::vector<std::vector<double>> *graph) {
    auto path = new std::vector<int>();
    eulerTourAlgorithm(start, path, mst);
    double path_length;

    createHamiltonianPath(path, &path_length, graph);
    return path_length;
}

std::vector<int> *findOdds(std::vector<std::vector<double>> *mst) {
    auto odds = new std::vector<int>();

    for (int i = 0; i < mst->size(); ++i) {
        if ((mst->at(i).size() % 2) != 0) {
            odds->push_back(i);
        }
    }
    return odds;
}

void findPerfectMatchingGreedyAlgorithm(std::vector<std::vector<double>> *mst,
                                        std::vector<std::vector<double>> *graph) {
    int closest;
    int length;
    std::vector<int>::iterator current_position;
    std::vector<int>::iterator first;

    auto odds = findOdds(mst);

    while (!odds->empty()) {
        first = odds->begin();
        std::vector<int>::iterator begin = odds->begin() + 1;
        length = std::numeric_limits<int>::max();
        for (; begin != odds->end(); ++begin) {
            if (graph->at(*first).at(*begin) < length) {
                length = graph->at(*first).at(*begin);
                closest = *begin;
                current_position = begin;
            }
        }
        mst->at(*first).push_back(closest);
        mst->at(closest).push_back(*first);
        odds->erase(current_position);
        odds->erase(first);
    }

    delete odds;
}

std::vector<std::vector<double>> *getMstPrimAlgorithm(std::vector<std::vector<double>> *graph) {
    int n = graph->size();
    auto mst = new std::vector<std::vector<double>>(n);
    auto key = new std::vector<int>(n, INT32_MAX);
    auto included = new std::vector<bool>(n);
    auto parent = new std::vector<int>(n);

    key->at(0) = 0;
    parent->at(0) = -1;

    for (int i = 0; i < n - 1; ++i) {
        auto k = getMinIndex(key, included, n);
        included->at(k) = true;

        for (int j = 0; j < n; ++j) {
            if (graph->at(k).at(j) && !included->at(j) && graph->at(k).at(j) < key->at(j)) {
                parent->at(j) = k;
                key->at(j) = graph->at(k).at(j);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        int j = parent->at(i);
        if (j != -1) {
            mst->at(i).push_back(j);
            mst->at(j).push_back(i);
        }
    }

    delete key;
    delete included;
    delete parent;
    return mst;
}

std::vector<std::pair<int, int>> *readCoordinates(int n) {
    auto coordinates = new std::vector<std::pair<int, int>>();
    int first;
    int second;

    for (int i = 0; i < n; ++i) {
        std::cin >> first >> second;
        coordinates->push_back({first, second});
    }

    return coordinates;
}

std::vector<std::vector<double>> *createGraph(std::vector<std::pair<int, int>> *coordinates) {
    auto table = createSquareTable(coordinates->size());

    for (size_t i = 0; i < coordinates->size(); ++i) {
        for (size_t j = 0; j < coordinates->size(); ++j) {
            table->at(i).at(j) = calculateDistance(coordinates->at(i), coordinates->at(j));
        }
    }

    return table;
}

int findBestStartIndex(std::vector<std::vector<double>> *mst, std::vector<std::vector<double>> *graph) {
    int amount = graph->size();
    auto current_path = createSquareTable(amount);
    double best = std::numeric_limits<double>::max();
    int best_index;
    for (size_t i = 0; i < amount; ++i) {
        double result = findBestPath(i, mst, graph);

        current_path->at(i).at(0) = i;
        current_path->at(i).at(1) = result;

        if (current_path->at(i).at(1) < best) {
            best_index = current_path->at(i).at(0);
            best = current_path->at(i).at(1);
        }
    }

    delete current_path;
    return best_index;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int amount;
    std::cin >> amount;

    auto coordinates = readCoordinates(amount);

    auto graph = createGraph(coordinates);
    delete coordinates;

    auto mst = getMstPrimAlgorithm(graph);

    findPerfectMatchingGreedyAlgorithm(mst, graph);

    auto best_index = findBestStartIndex(mst, graph);

    auto path = new std::vector<int>();

    eulerTourAlgorithm(best_index, path, mst);

    double cost;

    createHamiltonianPath(path, &cost, graph);

    for (int i = 0; i < path->size(); ++i) {
        std::cout << path->at(i) + 1 << ' ';
    }

    delete graph;
    delete mst;
    delete path;
    return 0;
}
