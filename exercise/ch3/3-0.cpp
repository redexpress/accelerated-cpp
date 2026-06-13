#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::cout << "Please enter your first name: ";
    std::string name;
    std::cin >> name;
    std::cout << "Hello, " << name << "!" << std::endl;

    std::cout << "Please enter your midterm and final exam grades: ";
    double midterm, final;
    std::cin >> midterm >> final;
    std::cout << "Enter all your homework grades, "
            "followed by end-of-file";
    int count = 0;
// #define USE_AVERAGE
#ifdef USE_AVERAGE
    double sum = 0;
    double x;

    while (std::cin >> x) {
        ++count;
        sum += x;
    }
#else
    std::vector<double> homework;
    double x;

    while (std::cin >> x)
        homework.push_back(x);

    auto size = homework.size();
    if (size == 0) {
        std::cout << std::endl << "You must enter your grades. "
                    << "Please try again." << std::endl;
        return 1;
    }
    sort(homework.begin(), homework.end());

    auto mid = size/2;
    double median;
    median = (size % 2 == 0) ? (homework[mid] + homework[mid-1]) / 2
            : homework[mid];
#endif
    std::streamsize  prec = std::cout.precision();
    std::cout << "Your final grade is " << std::setprecision(3)
        << 0.2 * midterm + 0.4 * final +
#ifdef USE_AVERAGE
            0.4 * sum / count
#else
            0.4 * midterm
#endif
        << std::setprecision(prec) << std::endl;

    return 0;
}