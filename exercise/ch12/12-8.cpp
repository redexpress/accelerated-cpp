#include "Str.h"
#include <iostream>
#include <sstream>
#include <cassert>

int main() {
    // Test getline with default delimiter '\n'
    {
        std::istringstream iss("hello world\nnext line");
        Str s;
        getline(iss, s);
        assert(s.size() == 11);
        assert(std::strcmp(s.c_str(), "hello world") == 0);

        getline(iss, s);
        assert(s.size() == 9);
        assert(std::strcmp(s.c_str(), "next line") == 0);
    }

    // Test getline with custom delimiter
    {
        std::istringstream iss("apple,banana,cherry");
        Str s;
        getline(iss, s, ',');
        assert(s.size() == 5);
        assert(std::strcmp(s.c_str(), "apple") == 0);

        getline(iss, s, ',');
        assert(s.size() == 6);
        assert(std::strcmp(s.c_str(), "banana") == 0);

        getline(iss, s, ',');
        assert(s.size() == 6);
        assert(std::strcmp(s.c_str(), "cherry") == 0);
    }

    // Test empty line
    {
        std::istringstream iss("\n");
        Str s;
        getline(iss, s);
        assert(s.size() == 0);
        assert(std::strcmp(s.c_str(), "") == 0);
    }

    // Test EOF
    {
        std::istringstream iss("last");
        Str s;
        getline(iss, s);
        assert(s.size() == 4);
        assert(std::strcmp(s.c_str(), "last") == 0);

        getline(iss, s);
        assert(iss.eof());
    }

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
