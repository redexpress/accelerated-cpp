#include <iomanip>
#include <iostream>
#include <string>

int main() {
    double limit = 999;
    int width1 = std::to_string(limit).length() + 1;
    int width2 = std::to_string(limit * limit).length() + 4;
    for (double i = 1; i <= limit; i+=1.0) {
        std::cout << std::setw(width1) << i
                << std::setw(width2) << i * i << std::endl;
    }
}
