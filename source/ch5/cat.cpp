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

vector<string> vcat(const vector<string>& top,
                const vector<string>& bottom)
{
    vector<string> ret = top;
    // for (vector<string>::const_iterator it = bottom.begin();
    //      it != bottom.end(); ++it)
    //     ret.push_back(*it);
    ret.insert(ret.end(), bottom.begin(), bottom.end());
    return ret;
}

vector<string> hcat(const vector<string>& left,
                const vector<string>& right)
{
    vector<string> ret;
    string::size_type width1 = width(left) + 1;
    vector<string>::size_type i = 0, j = 0;
    while (i != left.size() || j != right.size()) {
        string s;
        if (i != left.size())
            s += left[i++];

        s += string(width1 - s.size(), ' ');

        if (j != right.size())
            s += right[j++];

        ret.push_back(s);
    }
    return ret;
}

int main()
{
    vector<string> v1 = {"one", "two", "three"};
    vector<string> v2 = {"four", "five", "six", "seven"};
    vector<string> result = vcat(v1, v2);
    for (vector<string>::size_type i = 0; i != result.size(); ++i) {
        cout << result[i] << ", ";
    }
    cout << endl;
    result = hcat(v1, v2);
    for (vector<string>::size_type i = 0; i != result.size(); ++i) {
        cout << result[i] << endl;
    }
    cout << endl;
}
