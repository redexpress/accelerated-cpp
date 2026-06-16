#include "Str.h"
#include <iostream>
#include <cassert>
#include <new>

int main() {
    // 1. size of self-managing Str
    std::cout << "sizeof(Str) = " << sizeof(Str) << " bytes\n";
    assert(sizeof(Str) == sizeof(char*) + sizeof(Str::size_type));

    // 2. c_str() null-terminated invariant
    Str s("hello");
    assert(std::strcmp(s.c_str(), "hello") == 0);
    s[0] = 'H';
    assert(std::strcmp(s.c_str(), "Hello") == 0);

    // 3. copy ctor: deep copy, independent storage
    Str a("apple");
    Str b = a;
    assert(a.c_str() != b.c_str());
    assert(std::strcmp(a.c_str(), b.c_str()) == 0);
    b[0] = 'B';
    assert(std::strcmp(a.c_str(), "apple") == 0);
    assert(std::strcmp(b.c_str(), "Bpple") == 0);
    std::cout << "copy ctor: a=" << a << " b=" << b << "\n";

    // 4. copy assignment: deep copy + self-assignment safe
    Str c;
    c = a;
    assert(c.c_str() != a.c_str());
    assert(std::strcmp(c.c_str(), a.c_str()) == 0);
    Str* p = &a;
    a = *p;
    assert(std::strcmp(a.c_str(), "apple") == 0);
    std::cout << "copy assign: c=" << c << "\n";

    // 5. move-like growth via operator+=
    Str t;
    for (int i = 0; i < 100; ++i) t += Str("x");
    assert(t.size() == 100);
    std::cout << "t.size=" << t.size() << " (after 100 concats)\n";

    // 6. memory pressure: many Strs in a loop, no leaks under sanitizers
    for (int i = 0; i < 10000; ++i) {
        Str tmp(50, 'z');
        Str dst = tmp;
        dst += "tail";
    }
    std::cout << "10000 Str cycles ok\n";

    return 0;
}
