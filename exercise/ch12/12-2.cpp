#include "Str.h"
#include <iostream>
#include <cstring>
#include <cassert>

int main() {
    // 1. c_str() returns null-terminated C string
    Str a("hello");
    const char* cs = a.c_str();
    assert(std::strlen(cs) == 5);
    assert(std::strcmp(cs, "hello") == 0);
    std::cout << "c_str: " << cs << "\n";

    // 2. data() returns the underlying buffer (null-terminated in this Str)
    const char* dt = a.data();
    assert(dt == a.c_str());
    assert(std::strcmp(dt, "hello") == 0);
    std::cout << "data: " << dt << "\n";

    // 3. copy(dest, count): copies count chars, no null terminator written
    char buf1[10] = {0};
    a.copy(buf1, 3);
    assert(buf1[0] == 'h' && buf1[1] == 'e' && buf1[2] == 'l' && buf1[3] == 0);
    std::cout << "copy n=3: '" << buf1 << "'\n";

    // 4. copy(dest, count, pos): from a given position
    char buf2[10] = {0};
    a.copy(buf2, 5, 0);
    assert(std::strcmp(buf2, "hello") == 0);
    a.copy(buf2, 2, 1);
    assert(buf2[0] == 'e' && buf2[1] == 'l');
    std::cout << "copy pos=1 n=2: '" << buf2 << "'\n";

    // 5. copy count > remaining: only copies up to end
    char buf3[10] = {0};
    Str::size_type n = a.copy(buf3, 100, 2);
    assert(n == 3);
    assert(std::strcmp(buf3, "llo") == 0);
    std::cout << "copy pos=2 n=100 returned=" << n << " buf='" << buf3 << "'\n";

    // 6. copy default pos=0, full length
    char buf4[10] = {0};
    Str::size_type copied = a.copy(buf4, a.size());
    assert(copied == 5);
    assert(std::strcmp(buf4, "hello") == 0);
    std::cout << "copy full: '" << buf4 << "'\n";

    // 7. copy pos out of range throws
    bool threw = false;
    try {
        a.copy(buf1, 1, 100);
    } catch (const std::out_of_range&) {
        threw = true;
    }
    assert(threw);
    std::cout << "copy out_of_range: threw as expected\n";

    // 8. c_str survives a self-modify (re-allocation preserves null-term)
    Str b("short");
    const char* p1 = b.c_str();
    b += "_extended_payload";
    const char* p2 = b.c_str();
    assert(std::strcmp(p2, "short_extended_payload") == 0);
    assert(p2 != p1);
    std::cout << "c_str after grow: " << p2 << "\n";

    return 0;
}
