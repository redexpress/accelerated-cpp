#include <iostream>
#include <string>

int main() {
    std::cout << "Please enter your first name: ";
    std::string name;
    std::cin >> name;
    const auto greeting = "Hello, " + name + "!";
    const int pad = 0;
    const int rows = pad * 2 + 3;
    const auto cols = greeting.length() + pad * 2 + 2;
    std::cout << std::endl;

    for (int r = 0; r != rows; ++r) {
        auto c = 0;
        while (c != cols) {
            if (r == pad + 1 && c == pad + 1) {
                std::cout << greeting;
                c += greeting.size();
            } else {
                if (r == 0 || r == rows - 1 ||
                    c == 0 || c == cols - 1)
                    std::cout << "*";
                else
                    std::cout << " ";
                ++c;
            }
        }
        std::cout << std::endl;
    }
    return 0;
}
