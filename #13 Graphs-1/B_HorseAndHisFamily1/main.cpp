#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <string>

std::map<int, std::string> *fillMap(int amount) {
    auto *map = new std::map<int, std::string>();

    int input_number;
    std::string input_string;

    for (int i = 0; i < amount; ++i) {
        std::cin >> input_number;
        std::getline(std::cin, input_string);
        map->insert({input_number, input_string.substr(1)});
    }
    return map;
}

std::vector<std::vector<int>> *createTable(int n, int m) {
    auto table = new std::vector<std::vector<int>>(n);

    for (int i = 0; i < n; ++i) {
        table->at(i) = std::vector<int>(m);
    }

    return table;
}

std::vector<std::vector<std::string>> *createStringTable(int n, int m) {
    auto table = new std::vector<std::vector<std::string>>(n);

    for (int i = 0; i < n; ++i) {
        table->at(i) = std::vector<std::string>(m);
    }

    return table;
}

void addLinks(std::vector<std::vector<int>> *table, int number_of_links) {
    int first;
    int second;

    for (int i = 0; i < number_of_links; ++i) {
        std::cin >> first >> second;
        table->at(first).push_back(second);
        table->at(second).push_back(first);
    }
}

std::vector<int> *bfs(std::vector<std::vector<int>> *table, int start_position) {
    std::queue<int> q;
    q.push(start_position);
    std::vector<bool> used(table->size());
    auto distances = new std::vector<int>(table->size());
    std::vector<int> parents(table->size());
    used[start_position] = true;
    parents[start_position] = -1;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto to : table->at(v)) {
            if (!used[to]) {
                used[to] = true;
                q.push(to);
                distances->at(to) = distances->at(v) + 1;
                parents[to] = v;
            }
        }
    }

    return distances;
}

void printAnswer(std::vector<int> *answer, std::map<int, std::string> *map) {
    int max_level = *(std::max_element(answer->begin(), answer->end()));
    auto answer_table = createStringTable(max_level + 1, 0);

    for (int i = 0; i <= max_level; ++i) {
        for (size_t j = 0; j < map->size(); ++j) {
            if (answer->at(j) == i) {
                answer_table->at(i).push_back(map->at(j));
            }
        }
    }

    for (int i = 0; i <= max_level; ++i) {
        std::sort(answer_table->at(i).begin(), answer_table->at(i).end());

        for (size_t j = 0; j < answer_table->at(i).size(); ++j) {
            std::cout << answer_table->at(i).at(j) << '\n';
        }
    }

    delete answer_table;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number_of_relatives;
    int number_of_links;
    int number_of_organizer;

    std::cin >> number_of_relatives >> number_of_links;

    auto table = createTable(number_of_relatives, 0);
    auto map = fillMap(number_of_relatives);

    addLinks(table, number_of_links);
    std::cin >> number_of_organizer;

    auto answer = bfs(table, number_of_organizer);

    printAnswer(answer, map);

    delete table;
    delete map;
    delete answer;
    return 0;
}
