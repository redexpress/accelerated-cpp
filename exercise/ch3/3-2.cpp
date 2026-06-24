#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

template <class Iter>
void print_range(Iter begin, Iter end) {
    while (begin != end) {
        std::cout << *begin++ << ' ';
    }
    std::cout << std::endl;
}

int main() {
    std::istringstream in(
        "9 1 5 8 2 7 3 6 4 10 11 12"
    );

    std::vector<int> values;
    int x;

    while (in >> x) {
        values.push_back(x);
    }

    std::sort(values.begin(), values.end());

    std::vector<int>::size_type n = values.size();

    std::vector<int>::size_type q1 = n / 4;
    std::vector<int>::size_type q2 = n / 2;
    std::vector<int>::size_type q3 = n * 3 / 4;

    std::cout << "Q1: ";
    print_range(values.begin(), values.begin() + q1);

    std::cout << "Q2: ";
    print_range(values.begin() + q1, values.begin() + q2);

    std::cout << "Q3: ";
    print_range(values.begin() + q2, values.begin() + q3);

    std::cout << "Q4: ";
    print_range(values.begin() + q3, values.end());

    return 0;
}