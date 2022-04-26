#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <cstring>

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

std::map<int, std::string> *map;

bool mySort(const int &a, const int &b) {
    std::string &s1 = map->at(a);
    std::string &s2 = map->at(b);
    return !(std::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end()));
}

void addLinks(std::vector<std::vector<int>> *table, int number_of_links) {
    int first;
    int second;

    for (int i = 0; i < number_of_links; ++i) {
        std::cin >> first >> second;
        table->at(first).push_back(second);
        table->at(second).push_back(first);
    }

    for (size_t i = 0; i < table->size(); ++i) {
        std::sort(table->at(i).begin(), table->at(i).end(), mySort);
    }
}

std::vector<int> *dfs(std::vector<std::vector<int>> *table, int start_position) {
    std::stack<int> stack;
    stack.push(start_position);
    std::vector<bool> used(table->size());
    auto path = new std::vector<int>();
    while (!stack.empty()) {
        int v = stack.top();
        stack.pop();
        if (!used[v]) {
            path->push_back(v);
        }
        used[v] = true;
        for (auto to : table->at(v)) {
            if (!used[to]) {
                stack.push(to);
            }
        }
    }

    return path;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number_of_relatives;
    int number_of_links;
    int number_of_organizer;

    std::cin >> number_of_relatives >> number_of_links;

    auto table = createTable(number_of_relatives, 0);
    map = fillMap(number_of_relatives);

    addLinks(table, number_of_links);
    std::cin >> number_of_organizer;

    auto answer = dfs(table, number_of_organizer);

    for (size_t i = 0; i < map->size(); ++i) {
        std::cout << map->at(answer->at(i)) << '\n';
    }

    delete table;
    delete map;
    delete answer;
    return 0;
}
