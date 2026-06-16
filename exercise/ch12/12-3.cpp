#include "Str.h"
#include <iostream>
#include <cstring>
#include <cassert>

int main() {
    // 1. compare() returns strcmp-style int
    Str a("apple"), b("banana"), c("apple");
    int r1 = compare(a, b);
    int r2 = compare(b, a);
    int r3 = compare(a, c);
    assert(r1 < 0);
    assert(r2 > 0);
    assert(r3 == 0);
    std::cout << "compare(apple,banana)=" << r1 << " (apple,banana)\n";
    std::cout << "compare(banana,apple)=" << r2 << " (banana,apple)\n";
    std::cout << "compare(apple,apple) =" << r3 << " (apple,apple)\n";

    // 2. Operators all derive from compare()
    assert((a <  b) == true);
    assert((a >  b) == false);
    assert((a <= b) == true);
    assert((a >= b) == false);
    assert((a == c) == true);
    assert((a != b) == true);
    std::cout << "apple <  banana: " << std::boolalpha << (a <  b) << "\n";
    std::cout << "apple == apple : " << (a == c) << "\n";

    // 3. Lexicographic prefix rule: "abc" < "abcd"
    Str p("abc"), q("abcd");
    assert(compare(p, q) < 0);
    assert(p < q);
    std::cout << "abc < abcd: " << (p < q) << "\n";

    // 4. Empty string handling
    Str e1, e2;
    assert(compare(e1, e2) == 0);
    assert(e1 == e2);
    assert(compare(e1, a) < 0);
    assert(e1 < a);
    std::cout << "empty == empty: " << (e1 == e2) << "\n";
    std::cout << "empty < apple : " << (e1 < a) << "\n";

    // 5. compare() vs raw strcmp (must agree)
    Str s1("hello"), s2("world");
    assert(compare(s1, s2) == std::strcmp(s1.c_str(), s2.c_str()));
    assert(compare(s2, s1) == std::strcmp(s2.c_str(), s1.c_str()));
    std::cout << "compare() matches strcmp on c_str()\n";

    // 6. Sort Strs using compare() as comparator
    Str words[5] = { Str("pear"), Str("apple"), Str("orange"), Str("banana"), Str("kiwi") };
    std::sort(words, words + 5, [](const Str& x, const Str& y) { return compare(x, y) < 0; });
    std::cout << "sorted: ";
    for (int i = 0; i < 5; ++i) std::cout << words[i] << " ";
    std::cout << "\n";
    assert(words[0] == Str("apple"));
    assert(words[4] == Str("pear"));

    return 0;
}
