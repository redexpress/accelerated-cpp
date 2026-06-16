#include <iostream>
#include <vector>
#include <algorithm>

template <class T> T median(std::vector<T> v) {
    auto size = v.size();
    if (size == 0)
        throw std::domain_error("median of an empty vector");
    std::sort(v.begin(), v.end());
    auto mid = size/2;
    return size % 2 == 0 ? (v[mid] + v[mid-1]) / 2 : v[mid];
}

int main() {
    std::vector<double> v = {77, 88, 100};
    double value = median(v);
    std::cout << value << std::endl;
    return 0;
}