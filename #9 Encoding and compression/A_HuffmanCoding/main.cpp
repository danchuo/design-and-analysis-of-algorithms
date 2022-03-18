#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <vector>

struct Node {
    Node(char value, int frequency, Node *left_node, Node *right_node) {
        left = left_node;
        right = right_node;
        this->value = value;
        this->frequency = frequency;
    }

    ~Node() {
        delete left;
        delete right;
    }

    Node *left;
    Node *right;
    char value;
    int frequency;
};

struct Comparator {
    bool operator()(Node *left_node, Node *right_node) {
        return left_node->frequency > right_node->frequency;
    }
};

std::string encodeMessage(const std::string &input_string,
                          std::map<char, std::string> *codes_table) {
    std::string answer;
    for (auto symbol : input_string) {
        answer += codes_table->at(symbol);
    }
    return answer;
}

void computeCodes(Node *root, const std::string &code_string,
                  std::map<char, std::string> *codes_table) {
    if (root == nullptr) {
        return;
    }

    if (root->left == nullptr && root->right == nullptr) {
        codes_table->operator[](root->value) = code_string;
    }

    computeCodes(root->right, code_string + "1", codes_table);
    computeCodes(root->left, code_string + "0", codes_table);
}

Node *buildHuffmanTree(const std::map<char, int> &frequency_table) {
    std::priority_queue<Node *, std::vector<Node *>, Comparator> priority_queue;

    for (auto pair : frequency_table) {
        priority_queue.push(new Node(pair.first, pair.second, nullptr, nullptr));
    }

    if (priority_queue.size() == 1) {
        return new Node('\0', priority_queue.top()->frequency, priority_queue.top(), nullptr);
    }

    while (priority_queue.size() > 1) {
        auto left_node = priority_queue.top();
        priority_queue.pop();
        auto right_node = priority_queue.top();
        priority_queue.pop();

        priority_queue.push(
            new Node('\0', left_node->frequency + right_node->frequency, left_node, right_node));
    }

    return priority_queue.top();
}

void printTable(const std::map<char, std::string> &table) {
    for (auto pair : table) {
        std::cout << pair.first << ": " << pair.second << '\n';
    }
}

std::map<char, int> getFrequencyTable(const std::string &input_string) {
    std::map<char, int> frequency_table;

    for (auto symbol : input_string) {
        ++frequency_table[symbol];
    }

    return frequency_table;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string input_string;

    std::getline(std::cin, input_string);

    auto frequency_table = getFrequencyTable(input_string);
    auto root = buildHuffmanTree(frequency_table);
    std::map<char, std::string> codes_table;

    computeCodes(root, "", &codes_table);

    auto coded_message = encodeMessage(input_string, &codes_table);

    std::cout << frequency_table.size() << ' ' << coded_message.size() << '\n';
    printTable(codes_table);
    std::cout << coded_message << '\n' << '\n';

    delete root;
    return 0;
}
