#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> split(const std::string& s) {
    std::vector<std::string> ret;
    auto i = 0;
    while (i != s.size()) {
        while (i != s.size() && isspace(s[i]))
            ++i;
        auto j = i;
        while (j != s.size() && !isspace(s[j]))
            ++j;
        if (i != j) {
            ret.push_back(s.substr(i, j - i));
            i = j;
        }
    }
    return ret;
}

std::string::size_type width(const std::vector<std::string>& v) {
    std::string::size_type maxlen = 0;
    for (const auto& str : v) {
        maxlen = std::max(maxlen, str.size());
    }
    return maxlen;
}

std::vector<std::string> frame(const std::vector<std::string>& v) {
    std::vector<std::string> ret;
    std::string::size_type maxlen = width(v);
    std::string border(maxlen + 4, '*');
    ret.push_back(border);
    for (std::vector<std::string>::size_type i = 0; i != v.size(); ++i) {
        ret.push_back("* " + v[i] +
            std::string(maxlen - v[i].size(), ' ') + " *");
    }
    ret.push_back(border);
    return ret;
}

std::vector<std::string> vcat(const std::vector<std::string>& top,
                const std::vector<std::string>& bottom) {
    std::vector<std::string> ret = top;
    // for (vector<string>::const_iterator it = bottom.begin();
    //      it != bottom.end(); ++it)
    //     ret.push_back(*it);
    ret.insert(ret.end(), bottom.begin(), bottom.end());
    return ret;
}

std::vector<std::string> hcat(const std::vector<std::string>& left,
                const std::vector<std::string>& right) {
    std::vector<std::string> ret;
    std::string::size_type width1 = width(left) + 1;
    std::vector<std::string>::size_type i = 0, j = 0;
    while (i != left.size() || j != right.size()) {
        std::string s;
        if (i != left.size())
            s += left[i++];

        s += std::string(width1 - s.size(), ' ');

        if (j != right.size())
            s += right[j++];

        ret.push_back(s);
    }
    return ret;
}

int main() {
    std::vector<std::string> v1 = {"one", "two", "three"};
    std::string s2 = "four five six server";
    std::vector<std::string> v2 = split(s2);
    std::vector<std::string> result = vcat(v1, v2);
    for (const auto& s : result) {
        std::cout << s << ", ";
    }
    std::cout << std::endl;
    result = hcat(v1, frame(v2));
    for (const auto& s: result) {
        std::cout << s << std::endl;
    }
    std::cout << std::endl;
}
