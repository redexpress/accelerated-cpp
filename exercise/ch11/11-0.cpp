#include "Vec.h"

#include <iostream>
#include <string>
#include <stdexcept>

int main() {
    // 1. default ctor, push_back, size, capacity, operator[]
    Vec<int> v;
    for (int i = 0; i < 5; ++i) v.push_back(i * 10);
    std::cout << "size=" << v.size() << " capacity=" << v.capacity() << "\n";
    for (Vec<int>::size_type i = 0; i < v.size(); ++i)
        std::cout << "v[" << i << "]=" << v[i] << " ";
    std::cout << "\n";

    // 2. reserve never shrinks
    v.reserve(100);
    std::cout << "after reserve(100): size=" << v.size()
              << " capacity=" << v.capacity() << "\n";
    v.reserve(2);
    std::cout << "after reserve(2) (no shrink): capacity=" << v.capacity() << "\n";

    // 3. emplace_back in-place constructs std::string
    Vec<std::string> vs;
    vs.emplace_back(5, 'a');
    vs.emplace_back("hello");
    vs.push_back(std::string("world"));
    std::cout << "vs: ";
    for (auto& s : vs) std::cout << s << " ";
    std::cout << "\n";

    // 4. copy ctor and copy assignment
    Vec<std::string> vs2(vs);
    Vec<std::string> vs3;
    vs3 = vs;
    std::cout << "vs2 size=" << vs2.size() << " vs3 size=" << vs3.size() << "\n";
    vs2[0] = "CHANGED";
    std::cout << "vs[0]=" << vs[0] << " vs2[0]=" << vs2[0] << "\n";

    // 5. move ctor and move assignment
    Vec<std::string> vs4(std::move(vs3));
    std::cout << "vs4 size=" << vs4.size() << " vs3 size=" << vs3.size() << "\n";
    Vec<std::string> vs5;
    vs5 = std::move(vs4);
    std::cout << "vs5 size=" << vs5.size() << " vs4 size=" << vs4.size() << "\n";

    // 6. clear / empty
    vs5.clear();
    std::cout << "after clear: size=" << vs5.size()
              << " empty=" << std::boolalpha << vs5.empty() << "\n";

    // 7. std::sort (relies on iterator_category = contiguous_iterator_tag)
    Vec<int> u;
    int data[] = {5, 2, 8, 1, 4, 7, 3};
    for (int x : data) u.push_back(x);
    std::sort(u.begin(), u.end());
    std::cout << "sorted u: ";
    for (int x : u) std::cout << x << " ";
    std::cout << "\n";

    // 8. size-n ctor
    Vec<int> w(4, 7);
    std::cout << "Vec(4,7): ";
    for (int x : w) std::cout << x << " ";
    std::cout << "\n";

    // 9. erase single element
    Vec<int> e;
    for (int x : {10, 20, 30, 40, 50}) e.push_back(x);
    auto it = e.erase(e.begin() + 2);
    std::cout << "after erase(pos=2): size=" << e.size();
    for (int x : e) std::cout << " " << x;
    std::cout << " returned=" << *it << "\n";

    // 10. erase a range
    Vec<int> e2;
    for (int x : {1, 2, 3, 4, 5, 6, 7}) e2.push_back(x);
    auto it2 = e2.erase(e2.begin() + 1, e2.begin() + 4);
    std::cout << "after erase([1,4)): size=" << e2.size();
    for (int x : e2) std::cout << " " << x;
    std::cout << " returned=" << *it2 << "\n";

    // 11. erase-then-push_back to verify capacity preserved
    Vec<std::string> e3;
    for (int i = 0; i < 5; ++i) e3.push_back("s" + std::to_string(i));
    e3.reserve(20);
    std::cout << "before erase: size=" << e3.size()
              << " cap=" << e3.capacity() << "\n";
    e3.erase(e3.begin() + 1, e3.begin() + 3);
    std::cout << "after  erase: size=" << e3.size()
              << " cap=" << e3.capacity() << "\n";

    return 0;
}
