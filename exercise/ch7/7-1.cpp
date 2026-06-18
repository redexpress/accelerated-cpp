#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

int main() {
    std::string s;
    std::map<std::string, int> counters;
    std::istringstream input("apple banana apple cherry banana apple");
    while (input >> s)
        ++counters[s];
    std::map<int, std::vector<std::string>> groups;
    for (const auto& [w, cnt] : counters) {
        groups[cnt].push_back(w);
    }
    for (const auto& [cnt, words] : groups) {
        auto sorted_words = words;
        std::sort(sorted_words.begin(), sorted_words.end());
        for (const auto& w : sorted_words) {
            std::cout << w << '\t' << cnt << '\n';
        }
    }
    return 0;
}