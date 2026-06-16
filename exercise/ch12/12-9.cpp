#include "Str.h"
#include <iostream>
#include <sstream>
#include <cassert>

int main() {
    Str s("Hello, World!");
    std::ostringstream oss;
    oss << s;
    assert(oss.str() == "Hello, World!");

    Str empty;
    std::ostringstream oss2;
    oss2 << empty;
    assert(oss2.str() == "");

    Str repeated(5, 'x');
    std::ostringstream oss3;
    oss3 << repeated;
    assert(oss3.str() == "xxxxx");

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
