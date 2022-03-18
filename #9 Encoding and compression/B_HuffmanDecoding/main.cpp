#include <iostream>
#include <string>
#include <map>

std::map<std::string, char> *fillCodesTable(int number_of_strings) {
    auto codes_table = new std::map<std::string, char>();
    std::string input_string;
    std::getline(std::cin, input_string);

    for (int i = 0; i < number_of_strings; ++i) {
        std::getline(std::cin, input_string);
        codes_table->operator[](input_string.substr(3)) = input_string[0];
    }

    return codes_table;
}

std::string decodeString(const std::string &coded_string,
                         std::map<std::string, char> *codes_table) {
    std::string answer;
    std::string current_window;

    for (int i = 0; i < coded_string.size(); ++i) {
        current_window += coded_string[i];

        auto search = codes_table->find(current_window);
        if (search != codes_table->end()) {
            answer += codes_table->at(current_window);
            current_window = "";
        }
    }

    return answer;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int input_symbols;
    int output_symbols;
    std::cin >> input_symbols >> output_symbols;

    auto codes_table = fillCodesTable(input_symbols);

    std::string coded_symbols;
    std::getline(std::cin, coded_symbols);

    std::cout << decodeString(coded_symbols, codes_table);

    delete codes_table;
    return 0;
}
