#include <algorithm>
#include <iostream>
#include <iterator>
#include <ranges>
#include <map>
#include <random>
#include <string>
#include <vector>
#include <stdexcept>

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

using Rule = std::vector<std::string>;
using Rule_collection = std::vector<Rule>;
using Grammar = std::map<std::string, Rule_collection>;

Grammar read_grammar(std::istream& in) {
    Grammar ret;
    std::string line;

    while (getline(in, line)) {
        std::vector<std::string> entry = split(line);

        if (!entry.empty())
            ret[entry[0]].push_back(
                Rule(entry.begin() + 1, entry.end()));
    }
    return ret;
}

int nrand(int n) {
    if (n <= 0)
        throw std::domain_error("Argument to nrand is out of range");
    static std::mt19937 engine{std::random_device{}()};
    std::uniform_int_distribution<int> dist(0, n - 1);
    return dist(engine);
}

bool bracketed(const std::string& s) {
    return s.size() > 1 && s[0] == '<' && s[s.size() - 1] == '>';
}

void gen_aux(const Grammar& g, const std::string& word, std::vector<std::string>& ret) {
    if (!bracketed(word)) {
        ret.push_back(word);
    } else {
        Grammar::const_iterator it = g.find(word);
        if (it == g.end())
            throw std::logic_error("empty rule");

        const Rule_collection& c = it->second;

        const Rule& r = c[nrand(c.size())];

        for (const auto& word : r)
            gen_aux(g, word, ret);
    }
}

std::vector<std::string> gen_sentence(const Grammar& g) {
    std::vector<std::string> ret;
    gen_aux(g, "<sentence>", ret);
    return ret;
}

int main() {
    std::vector<std::string> sentence = gen_sentence(read_grammar(std::cin));
    auto joined = sentence | std::views::join_with(' ');
    std::ranges::copy(joined, std::ostream_iterator<char>(std::cout));
    std::cout << '\n';
    return 0;
}