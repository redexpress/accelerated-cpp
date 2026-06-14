#include <iomanip>
#include <iostream>
#include <string>

int main() {
    int limit = 999;
    int width1 = std::to_string(limit).length() + 1;
    int width2 = std::to_string(limit * limit).length() + 4;
    for (int i = 1; i <= limit; i++) {
        std::cout << std::setw(width1) << i
                << std::setw(width2) << i * i << std::endl;
    }
}
