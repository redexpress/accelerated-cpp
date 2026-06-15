#include <iostream>
#include <string>
#include <vector>
#include <map>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::map;

int main()
{
    string s;
    map<string, int> counters;
    while (cin >> s)
        ++counters[s];
    for (map<string, int>::const_iterator it = counters.begin();
         it != counters.end(); ++it) {
        cout << it->first << "\t" << it->second << endl;
    }
    return 0;
}