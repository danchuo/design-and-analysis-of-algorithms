#include <iostream>
#include <string>
#include <vector>

int calculateMaximumLengthOfASubsequence(const std::string &first, const std::string &second) {
    std::vector<int> lcs(second.length());
    int previous_data;
    int counter = 0;
    for (int index = 1; index < first.length(); ++index) {
        for (int j_index = 1; j_index < second.length(); ++j_index) {
            previous_data = lcs[j_index];
            if (first[index] == second[j_index]) {
                lcs[j_index] = counter + 1;
            } else {
                if (lcs[j_index] >= lcs[j_index - 1]) {
                    lcs[j_index] = lcs[j_index];
                } else {
                    lcs[j_index] = lcs[j_index - 1];
                }
            }
            counter = previous_data;
        }
    }

    return lcs[second.length() - 1];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string first;
    std::string second;

    std::getline(std::cin, first);
    std::getline(std::cin, second);

    int answer = first.length() > second.length()
                     ? calculateMaximumLengthOfASubsequence(first, second)
                     : calculateMaximumLengthOfASubsequence(second, first);

    std::cout << answer;

    return 0;
}
