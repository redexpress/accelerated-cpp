#include <iomanip>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::cout << "Please enter your first name: ";
    std::string name;
    std::istringstream input("Yang");
    input >> name;
    std::cout << "Hello, " << name << "!" << std::endl;

    std::cout << "Please enter your midterm and final exam grades: ";
    double midterm, final;
    std::istringstream input2("80 90");
    input2 >> midterm >> final;
    std::cout << "\nEnter all your homework grades, "
            "followed by end-of-file";
    int count = 0;
// #define USE_AVERAGE
#ifdef USE_AVERAGE
    double sum = 0;
    double x;

    std::istringstream input3("85 90 78 92 88");
    while (input3 >> x) {
        ++count;
        sum += x;
    }
#else
    std::vector<double> homework;
    double x;

    std::istringstream input3("85 90 78 92 88");
    while (input3 >> x)
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
    std::cout << "\nYour final grade is " << std::setprecision(3)
        << 0.2 * midterm + 0.4 * final +
#ifdef USE_AVERAGE
            0.4 * sum / count
#else
            0.4 * midterm
#endif
        << std::setprecision(prec) << std::endl;

    return 0;
}