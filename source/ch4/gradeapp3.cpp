#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <istream>
#include <string>
#include <vector>
#include <stdexcept>
#include "grade.h"
#include "Student_info.h"

using std::cin;      using std::sort;
using std::cout;     using std::streamsize;
using std::endl;     using std::string;
using std::vector;
using std::setprecision;
using std::domain_error;
using std::istream;
using std::max;
using std::setw;

int main()
{
    vector<Student_info> students;
    Student_info record;
    string::size_type maxlen = 0;

    while (read(cin, record)) {
        maxlen = max(maxlen, record.name.size());
        students.push_back(record);
    }
    sort(students.begin(), students.end(), compare);

    for (vector<Student_info>::size_type i = 0;
        i != students.size(); ++i) {
        cout << setw(maxlen+1) << students[i].name;
        try {
            double final_grade = grade(students[i]);
            streamsize  prec = cout.precision();
            cout << "Your final grade is " << setprecision(3)
                << final_grade << setprecision(prec) << endl;
        } catch (domain_error e) {
            cout << e.what();
        }
        cout << endl;
    }

    return 0;
}