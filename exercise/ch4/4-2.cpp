#include <iomanip>
#include <iostream>

int main() {
    for (int i = 1; i <= 100; i++) {
        std::cout << std::setw(4) << i
                << std::setw(8) << i * i << std::endl;
    }
}