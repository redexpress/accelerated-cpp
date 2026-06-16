#include "Str.h"
#include <iostream>
#include <cassert>

int main() {
    // 1. operator== returns true iff strcmp == 0
    Str a("hello"), b("hello"), c("world");
    assert((a == b) == true);
    assert((a == c) == false);
    std::cout << "hello == hello : " << std::boolalpha << (a == b) << "\n";
    std::cout << "hello == world : " << (a == c) << "\n";

    // 2. operator!= is logical complement of operator==
    assert((a != b) == false);
    assert((a != c) == true);
    std::cout << "hello != hello : " << (a != b) << "\n";
    std::cout << "hello != world : " << (a != c) << "\n";

    // 3. Length-mismatch is inequality even if prefix matches
    Str p("abc"), q("abcd");
    assert((p == q) == false);
    assert(p != q);
    std::cout << "abc == abcd     : " << (p == q) << "\n";
    std::cout << "abc != abcd     : " << (p != q) << "\n";

    // 4. Self-equality
    Str x("anything");
    assert(x == x);
    assert(!(x != x));
    std::cout << "x == x          : " << (x == x) << "\n";

    // 5. Empty strings are equal to themselves
    Str e1, e2;
    assert(e1 == e2);
    assert(!(e1 != e2));
    std::cout << "empty == empty  : " << (e1 == e2) << "\n";

    // 6. Empty vs non-empty is not equal
    assert(e1 != a);
    assert(!(e1 == a));
    std::cout << "empty != hello  : " << (e1 != a) << "\n";

    return 0;
}
