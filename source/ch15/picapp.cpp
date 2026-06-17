#include <string>
#include <vector>
#include "Pic.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;

int main()
{
    vector<string> v = {"one", "two", "three"};
    Picture p(v);
    cout << p << endl;

    Picture p2 = frame(p);
    cout << p2 << endl;

    Picture p3 = hcat(p, p2);
    cout << p3 << endl;

    Picture p4 = vcat(p3, p2);
    cout << p4 << endl;
    return 0;
}