#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
    std::istringstream input("49 82 75 91 63 58 100 87 72");

    std::vector<double> homework;
    double x;

    while (input >> x) {
        homework.push_back(x);
    }

    std::sort(homework.begin(), homework.end());
    std::vector<double>::size_type mid = homework.size() / 2;
    double median;
    if (homework.size() % 2 == 0) {
        median = (homework[mid] + homework[mid - 1]) / 2;
    } else {
        median = homework[mid];
    }
    std::cout << "median = " << median << std::endl;
}