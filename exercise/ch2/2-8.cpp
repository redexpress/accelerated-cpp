#include <cassert>
#include <iostream>

int main() {
    int result = 1;
    for (int i = 1; i < 10; ++i) {
        result *= i;
    }
    std::cout << result << std::endl;
    assert(result == 362880);
}