#include <algorithm>

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include "Core.h"

using std::cout;
using std::endl;
using std::cin;
using std::domain_error;
using std::setprecision;
using std::setw;
using std::sort;
using std::streamsize;
using std::string;
using std::vector;

using std::max;

int main()
{
    vector<Core*> students;
    Core* record;
    char ch;
    string::size_type maxlen = 0;

    while (cin>>ch) {
        if (ch=='U')
            record = new Core;
        else
            record = new Grad;
        record->read(cin);
        maxlen = max(maxlen, record->name().size());
        students.push_back(record);
    }

    sort(students.begin(), students.end(), compare_core_ptrs);

    for (vector<Core>::size_type i = 0; i != students.size(); ++i) {
        cout<<setw(maxlen+1)<<students[i]->name();
        try {
            double final_grade = students[i]->grade();
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade
                 << setprecision(prec) << endl;
        } catch (domain_error e) {
            cout << e.what() << endl;
        }
        delete students[i];
    }
    return 0;
}