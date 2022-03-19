#include <iostream>
#include <string>
#include <map>

std::map<std::string, char> *fillCodesTable(int number_of_strings) {
    auto codes_table = new std::map<std::string, char>();
    char input_symbol;
    char colon_symbol;
    std::string input_string;

    for (int i = 0; i < number_of_strings; ++i) {
        std::cin >> input_symbol;
        std::cin >> colon_symbol;
        std::cin >> input_string;
        codes_table->operator[](input_string) = input_symbol;
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
    int number_of_input_symbols;
    int number_of_coded_symbols;
    std::cin >> number_of_input_symbols;
    std::cin >> number_of_coded_symbols;

    auto codes_table = fillCodesTable(number_of_input_symbols);

    std::string coded_symbols;
    coded_symbols.reserve(number_of_coded_symbols / 2);
    char input_char;
    for (int i = 0; i < number_of_coded_symbols; ++i) {
        std::cin >> input_char;
        coded_symbols += input_char;
    }

    std::cout << decodeString(coded_symbols, codes_table);

    delete codes_table;
    return 0;
}
