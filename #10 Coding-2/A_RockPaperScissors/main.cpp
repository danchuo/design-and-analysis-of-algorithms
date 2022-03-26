#include <iostream>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int rock_r, paper_r, scissors_r;
    int rock_m, paper_m, scissors_m;

    std::cin >> rock_r >> paper_r >> scissors_r;
    std::cin >> rock_m >> paper_m >> scissors_m;

    std::cout << std::min(rock_r, paper_m) + std::min(paper_r, scissors_m) +
                     std::min(scissors_r, rock_m);

    return 0;
}
