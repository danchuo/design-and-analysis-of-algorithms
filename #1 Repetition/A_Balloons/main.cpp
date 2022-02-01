#include <iostream>
#include <vector>

std::vector<int>* fillVector(int number) {
    std::vector<int>* vector = new std::vector<int>();
    int input_number;

    for (int i = 0; i < number; ++i) {
        std::cin >> input_number;
        vector->push_back(input_number);
    }

    return vector;
}

int findNumberOfDeletedBalloons(std::vector<int>* vector) {
    int deleted_balloons = 0;

    int balloons_in_a_row = 1;

    if (vector->size() > 2) {
        for (int i = 0; i < vector->size(); ++i) {
            if (i != 0) {
                if (vector->at(i - 1) == vector->at(i)) {
                    ++balloons_in_a_row;



                } else {
                    balloons_in_a_row = 1;
                }
            }
        }
    }

    return deleted_balloons;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number_of_balloons;
    std::cin >> number_of_balloons;

    auto list = fillVector(number_of_balloons);

    delete list;
    return 0;
}
