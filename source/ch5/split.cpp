#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::getline;
using std::isspace;
using std::max;

vector<string> split(const string& s)
{
    vector<string> ret;
    typedef string::size_type string_size;
    string_size i = 0;
    while (i != s.size()) {
        while (i != s.size() && isspace(s[i]))
            ++i;
        string_size j = i;
        while (j != s.size() && !isspace(s[j]))
            ++j;
        if (i != j) {
            ret.push_back(s.substr(i, j - i));
            i = j;
        }
    }
    return ret;
}

string::size_type width(const vector<string>& v)
{
    string::size_type maxlen = 0;
    for (vector<string>::size_type i = 0; i != v.size(); ++i)
        maxlen = max(maxlen, v[i].size());
    return maxlen;
}

vector<string> frame(const vector<string>& v)
{
    vector<string> ret;
    string::size_type maxlen = width(v);
    string border(maxlen + 4, '*');
    ret.push_back(border);
    for (vector<string>::size_type i = 0; i != v.size(); ++i) {
        ret.push_back("* " + v[i] +
            string(maxlen - v[i].size(), ' ') + " *");
    }
    ret.push_back(border);
    return ret;
}

int main()
{
    string s;
    while (getline(cin, s)) {
        vector<string> v = split(s);
        for (vector<string>::size_type i = 0; i != v.size(); ++i) {
            cout << v[i] << endl;
        }
        vector<string> box = frame(v);
        for (vector<string>::size_type i = 0; i != box.size(); ++i) {
            cout << box[i] << endl;
        }
    }
    return 0;
}
