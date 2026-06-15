#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

std::size_t width(const std::vector<std::string>& v) {
    std::size_t maxlen = 0;
    for (const auto& s : v)
        maxlen = std::max(maxlen, s.size());
    return maxlen;
}

std::vector<std::string> frame(const std::vector<std::string>& v) {
    std::vector<std::string> ret;
    auto maxlen = width(v);
    std::string border(maxlen + 4, '*');
    ret.push_back(border);
    for (auto it = v.begin(); it != v.end(); ++it) {
        ret.push_back("* " + *it + std::string(maxlen - it->size(), ' ') + " *");
    }
    ret.push_back(border);
    return ret;
}

std::vector<std::string> vcat(const std::vector<std::string>& top,
                const std::vector<std::string>& bottom) {
    std::vector<std::string> ret = top;
    ret.insert(ret.end(), bottom.begin(), bottom.end());
    return ret;
}

std::vector<std::string> hcat(const std::vector<std::string>& left,
                const std::vector<std::string>& right) {
    std::vector<std::string> ret;
    std::string::size_type width1 = width(left) + 1;
    auto it_left = left.begin();
    auto it_right = right.begin();
    while (it_left != left.end() || it_right != right.end()) {
        std::string s;
        if (it_left != left.end()) {
            s += *it_left;
            ++it_left;
        }

        s += std::string(width1 - s.size(), ' ');

        if (it_right != right.end()) {
            s += *it_right;
            ++it_right;
        }

        ret.push_back(s);
    }
    return ret;
}

std::vector<std::string> split(const std::string_view str) {
    std::vector<std::string> ret;

    auto i = str.begin();
    while (i != str.end()) {
        i = std::find_if(i , str.end(), [](unsigned char c) {
                return !std::isspace(c);
            });
        auto j = std::find_if(i, str.end(), [](unsigned char c) {
                return std::isspace(c);
            });
        if (i != str.end())
            ret.emplace_back(i, j);
        i = j;
    }
    return ret;
}

int main() {
    std::vector<std::string> v1 = split("one two three");
    std::vector<std::string> v2 = {"four", "five", "six", "seven"};
    std::vector<std::string> result = vcat(v1, v2);
    for (std::vector<std::string>::size_type i = 0; i != result.size(); ++i) {
        std::cout << result[i] << ", ";
    }
    std::cout << std::endl;
    result = hcat(v1, v2);
    for (std::vector<std::string>::size_type i = 0; i != result.size(); ++i) {
        std::cout << result[i] << std::endl;
    }
    std::cout << std::endl;
}
