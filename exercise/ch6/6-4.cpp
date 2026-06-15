#include <iostream>
#include <vector>

int main() {
    std::vector<int> u(10, 100);
    std::vector<int> v;
    copy(u.begin(), u.end(), std::back_inserter(v));
    for (auto val : v) {
        std::cout << val << std::endl;
    }
    std::cout << "----------------\n";
    std::vector<int> v2(u.size(), 0);
    copy(u.begin(), u.end(), v2.begin());
    for (auto val : v2) {
        std::cout << val << std::endl;
    }
}