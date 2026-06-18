#include <iostream>
#include <sstream>

int main () {
    std::cout << "Please enter two number A, B: ";
    int a, b;
    std::istringstream input("3 5");
    input >> a >> b;
    if (a < b) {
        std::cout << "B is greater than A";
    } else if (a > b) {
        std::cout << "A is greater than B";
    } else {
        std::cout << "A is equal to B";
    }
    return 0;
}