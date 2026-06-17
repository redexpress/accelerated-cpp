#include <string>
#include <vector>
#include "Pic.h"

int main() {
    std::vector<std::string> v = {"one", "two", "three"};
    Picture p(v);
    std::cout << p << std::endl;

    Picture p2 = frame(p);
    std::cout << p2 << std::endl;

    Picture p3 = hcat(p, p2);
    std::cout << p3 << std::endl;

    Picture p4 = vcat(p3, p2);
    std::cout << p4 << std::endl;
    return 0;
}