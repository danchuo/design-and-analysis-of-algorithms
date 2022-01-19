#include <iostream>
#include <vector>
#include <deque>

void superMinimum(int numbers, int period);

void dequePushBack(std::deque<int> *deque, int element);

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int numbers;
    int period;
    std::cin >> numbers >> period;
    superMinimum(numbers, period);

    return 0;
}

void dequePushBack(std::deque<int> *deque, int element) {
    while (!deque->empty() && (element < deque->back())) {
        deque->pop_back();
    }

    deque->push_back(element);
}

void superMinimum(int const numbers, int const period) {
    std::deque<int> current_minimums;
    std::vector<int> current_period_elements(period);

    int current_number_in_period = 0;

    for (int i = 0; i < period; ++i) {
        std::cin >> current_period_elements[i];

        dequePushBack(&current_minimums, current_period_elements[i]);
    }

    std::cout << current_minimums.front() << '\n';

    for (int index = 0; index < numbers - period; ++index) {
        if (current_period_elements[current_number_in_period % period] ==
            current_minimums.front()) {
            current_minimums.pop_front();
        }

        std::cin >> current_period_elements[current_number_in_period % period];

        dequePushBack(&current_minimums,
                      current_period_elements[current_number_in_period % period]);

        ++current_number_in_period;
        std::cout << current_minimums.front() << '\n';
    }
}
