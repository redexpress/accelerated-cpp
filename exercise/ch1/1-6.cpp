#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::cout << "What is your name? ";
    std::string name;
    std::istringstream input("Yang Lu");
    input >> name;
    std::cout << "Hello, " << name
            << std::endl;
    input >> name;
    std::cout << "Hello, " << name
            << "; nice to meet you too!" << std::endl;
    return 0;
}