#include "Str.h"
#include <iostream>
#include <cassert>
#include <cstring>

int main() {
    // 1. Non-empty Str is truthy
    Str a("hello");
    if (a) std::cout << "a is truthy\n";
    assert(a);
    assert(!a == false);

    // 2. Empty Str is falsy
    Str b;
    if (!b) std::cout << "b is falsy\n";
    assert(!b);
    assert(!b == true);

    // 3. Default-constructed Str is falsy
    Str c;
    assert(!c);

    // 4. Str::operator bool used to test input state
    Str w;
    if (std::cin >> w) {
        assert(w);
        std::cout << "read word ok: " << w << "\n";
    } else {
        std::cout << "no input piped (expected when stdin is empty)\n";
    }

    // 5. Logical operators
    assert((a && true) == true);
    assert((Str() && true) == false);
    assert((Str() || true) == true);
    assert((a || false) == true);
    assert((!a || false) == false);

    // 6. Ternary
    Str d("x");
    const char* r = d ? "yes" : "no";
    assert(std::strcmp(r, "yes") == 0);
    std::cout << "ternary: " << r << "\n";

    // 7. After clearing a non-empty Str, it becomes falsy
    Str e("payload");
    assert(e);
    e = Str();
    assert(!e);
    std::cout << "cleared: falsy ok\n";

    return 0;
}
