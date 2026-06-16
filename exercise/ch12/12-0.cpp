#include "Str.h"
#include <iostream>
#include <sstream>
#include <algorithm>

int main() {
    // 1. default ctor, c-string ctor, size
    Str a;
    Str b("hello");
    std::cout << "a.size=" << a.size() << " b=" << b << " b.size=" << b.size() << "\n";

    // 2. count ctor
    Str c(5, 'x');
    std::cout << "c=" << c << "\n";

    // 3. iterator range ctor
    Str d(b.begin(), b.end());
    std::cout << "d=" << d << "\n";

    // 4. operator[] read/write
    b[0] = 'H';
    std::cout << "b after b[0]='H': " << b << "\n";

    // 5. operator+=, operator+
    Str e = b;
    e += Str(" world");
    Str f = b + Str("!") + Str("?");
    std::cout << "e=" << e << " f=" << f << "\n";

    // 6. comparison
    std::cout << std::boolalpha;
    std::cout << "Str(\"abc\") < Str(\"abd\") = " << (Str("abc") < Str("abd")) << "\n";
    std::cout << "Str(\"abc\") == Str(\"abc\") = " << (Str("abc") == Str("abc")) << "\n";
    std::cout << "Str(\"abc\") != Str(\"abd\") = " << (Str("abc") != Str("abd")) << "\n";

    // 7. iteration via begin/end
    std::cout << "b chars: ";
    for (Str::const_iterator it = b.begin(); it != b.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";

    // 8. operator>> (skip whitespace, read one word)
    std::istringstream iss("  foo bar baz");
    Str word;
    iss >> word;
    std::cout << "iss>>word: " << word << " | remaining='" << iss.str().substr(iss.tellg()) << "'\n";

    // 9. getline (read until newline)
    std::istringstream iln("first line\nsecond");
    Str line;
    getline(iln, line);
    std::cout << "getline: " << line << " | remaining='" << iln.str().substr(iln.tellg()) << "'\n";

    // 10. range-for and std::find
    Str g("abcdef");
    auto it = std::find(g.begin(), g.end(), 'd');
    std::cout << "find 'd' in " << g << " at pos " << (it - g.begin()) << "\n";

    return 0;
}
