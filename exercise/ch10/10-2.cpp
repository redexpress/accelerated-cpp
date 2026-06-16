#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

template <class T> typename T::value_type median(const T& c) {
    typedef typename T::size_type size_type;
    size_type size = c.size();
    if (size == 0)
        throw std::domain_error("median of an empty container");
    std::vector<typename T::value_type> v(c.begin(), c.end());
    std::sort(v.begin(), v.end());
    size_type mid = size / 2;
    return size % 2 == 0 ? (v[mid] + v[mid - 1]) / 2 : v[mid];
}

template <class T, std::size_t N> T median(const T (&a)[N]) {
    if (N == 0)
        throw std::domain_error("median of an empty array");
    std::vector<T> v(a, a + N);
    std::sort(v.begin(), v.end());
    std::size_t mid = N / 2;
    return N % 2 == 0 ? (v[mid] + v[mid - 1]) / 2 : v[mid];
}
