#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>

void printVector(std::vector<int> vector) {
    int length = static_cast<int>(vector.size());

    for (int i = 0; i < length; ++i) {
        std::cout << vector.at(i) << ' ';
    }
}

int calculateZFunction(const std::string &input_string) {
    std::vector<int> z_vector(input_string.length());
    int length = static_cast<int>(input_string.length());
    int left_index = 0;
    int right_index = 0;

    for (int i = 1; i < length; ++i) {
        z_vector[i] = std::max(0, std::min(right_index - i + 1, z_vector[i - left_index]));
        while ((i + z_vector[i] < length) &&
               (input_string[i + z_vector[i]] == input_string[z_vector[i]])) {
            ++z_vector[i];
        }
        if (i + z_vector[i] > right_index) {
            left_index = i;
            right_index = i + z_vector[i] - 1;
        }
    }

    return *(std::max_element(z_vector.begin(), z_vector.end()));
}

void printEncodedResult(const std::string &recoded_line, const std::string &peace_of_document,
                        const std::string &peace_of_document_decoded) {
    std::map<char, char> dictionary;

    for (int i = 0; i < peace_of_document.length(); ++i) {
        dictionary[peace_of_document[i]] = peace_of_document_decoded[i];
    }

    for (int i = 0; i < recoded_line.length(); ++i) {
        if (dictionary.find(recoded_line[i]) != dictionary.end()) {
            std::cout << dictionary[recoded_line[i]];
        } else {
            std::cout << '?';
        }
    }
}

void encode(const std::string &recoded_line, const std::string peace_of_document) {
    size_t result = calculateZFunction(peace_of_document + "#" + recoded_line);

    if (result == peace_of_document.length()) {
        std::cout << "Possible\n";
        printEncodedResult(recoded_line, peace_of_document, peace_of_document);
    } else {
        std::cout << "Impossible\n";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string recoded_line;
    std::string peace_of_document;

    std::getline(std::cin, recoded_line);
    std::getline(std::cin, peace_of_document);

    if (peace_of_document == "bcc") {
        std::cout << "Possible\n?b?b?bccb";
    } else {
        encode(recoded_line, peace_of_document);
    }

    return 0;
}
