#include <iostream>
#include <numeric>
#include <vector>
#include <expected>

std::expected<double, int> average(const std::vector<double>& vec) {
    if (vec.empty()) {
        return std::unexpected(1);
    }
    double sum = std::accumulate(vec.begin(), vec.end(), 0.0);
    return sum / vec.size();
}

int main() {
    std::vector vec = {1.0, 2.0, 3.0};
    auto result = average(vec);
    if (result.has_value()) {
        std::cout << result.value() << std::endl;
    } else {
        std::cout << result.error() << std::endl;
    }
    return 0;
}