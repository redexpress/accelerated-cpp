#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

using std::vector;
using std::string;

bool not_url_char(unsigned char c) {
    static const string url_ch = "~;/?:@=&$-_.+!*'(),";
    return !(std::isalnum(c) || url_ch.contains(c));
}

auto url_end(auto b, auto e) {
    return std::find_if(b, e, not_url_char);
}

auto url_beg(auto b, auto e) {
    static constexpr std::string_view sep = "://";

    auto i = b;
    while ((i = std::search(i, e, sep.begin(), sep.end())) != e) {
        if (i != b && i + sep.size() != e) {
            auto beg = i;
            while (beg != b && std::isalpha(static_cast<unsigned char>(beg[-1])))
                --beg;
            if (beg != i && !not_url_char(static_cast<unsigned char>(i[sep.size()])))
                return beg;
        }
        i += sep.size();
    }
    return e;
}

vector<string> find_urls(std::string_view s) {
    vector<string> ret;

    auto b = s.begin(), e = s.end();
    while (b != e) {
        b = url_beg(b, e);
        if (b != e) {
            auto after = url_end(b, e);
            ret.emplace_back(b, after);
            b = after;
        }
    }
    return ret;
}

int main() {
    string test_str = "Visit http://www.example.com or https://secure.site.org/path?q=1 for more info. "
                      "Invalid: ://missing-protocol.com and ftp://valid-ftp.net/files. "
                      "End of test.";

    vector<string> urls = find_urls(test_str);

    std::cout << "Found " << urls.size() << " URLs:" << std::endl;
    for (auto i = 0; i < urls.size(); ++i) {
        std::cout << (i + 1) << ": " << urls[i] << std::endl;
    }

    return 0;
}