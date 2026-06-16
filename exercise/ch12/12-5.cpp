#include "Str.h"
#include <iostream>
#include <cassert>

int main() {
    Str s("world");

    // 1. Str + const char* (the easy direction was already fine)
    Str r1 = s + "!";
    assert(r1 == Str("world!"));
    std::cout << "s + \"!\"         = " << r1 << "\n";

    // 2. const char* + Str: must NOT call Str(const char*)
    Str r2 = "hello, " + s;
    assert(r2 == Str("hello, world"));
    std::cout << "\"hello, \" + s  = " << r2 << "\n";

    // 3. Empty literal + Str
    Str r3 = "" + s;
    assert(r3 == Str("world"));
    std::cout << "\"\" + s          = " << r3 << "\n";

    // 4. Str + empty literal
    Str r4 = s + "";
    assert(r4 == Str("world"));
    std::cout << "s + \"\"          = " << r4 << "\n";

    // 5. Longer concatenation chain
    Str r5 = "[" + s + "]";
    assert(r5 == Str("[world]"));
    std::cout << "\"[\" + s + \"]\"  = " << r5 << "\n";

    // 6. Verify c_str() is null-terminated after concat
    assert(std::strcmp(r2.c_str(), "hello, world") == 0);
    std::cout << "c_str matches    : ok\n";

    return 0;
}
