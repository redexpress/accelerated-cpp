#include "Str.h"
#include <iostream>
#include <algorithm>
#include <cassert>

int main() {
    Str s("hello, world");

    // 1. begin/end return Str::iterator
    Str::iterator it = s.begin();
    Str::iterator e  = s.end();
    assert(*it == 'h');
    assert(*(e - 1) == 'd');
    assert((e - it) == 12);

    // 2. const overload
    const Str& cs = s;
    Str::const_iterator cit = cs.begin();
    Str::const_iterator cend = cs.end();
    assert(*cit == 'h');
    assert((cend - cit) == 12);

    // 3. range-for uses begin()/end()
    int n = 0;
    for (char c : s) {
        (void)c;
        ++n;
    }
    assert(n == 12);

    // 4. random access: += / -= / + / - / []
    Str::iterator p = s.begin() + 7;
    assert(*p == 'w');
    assert(p[0] == 'w');
    assert(p[-1] == ' ');
    p += 1;
    assert(*p == 'o');
    p -= 3;
    assert(*p == ',');

    // 5. five-way comparison
    Str::iterator a = s.begin();
    Str::iterator b = s.begin() + 1;
    assert(a < b);
    assert(a <= b);
    assert(b > a);
    assert(b >= a);
    assert(a != b);
    assert(a == s.begin());

    // 6. ++ / -- / postfix
    Str::iterator i = s.begin();
    assert(*(i++) == 'h');
    assert(*i == 'e');
    assert(*(--i) == 'h');
    assert(*(i--) == 'h');
    assert(i == s.begin());

    // 7. STL algorithms work
    auto itcomma = std::find(s.begin(), s.end(), ',');
    assert(itcomma == s.begin() + 5);
    assert(std::distance(s.begin(), s.end()) == 12);

    // 8. iterator -> const_iterator implicit conversion
    Str::const_iterator from_it = s.begin();
    assert(*from_it == 'h');

    // 9. std::sort via random_access_iterator_tag dispatch
    Str shuffled("dcba");
    std::sort(shuffled.begin(), shuffled.end());
    assert(shuffled == Str("abcd"));
    std::cout << "sorted: " << shuffled << "\n";

    return 0;
}
