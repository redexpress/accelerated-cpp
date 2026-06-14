#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <stdexcept>
#include "grade.h"
#include "Student_info.h"
#include "median.h"

using std::cin;      using std::sort;
using std::cout;     using std::streamsize;
using std::endl;     using std::string;
using std::vector;
using std::setprecision;
using std::domain_error;
using std::istream;
using std::ostream;
using std::max;
using std::setw;
using std::find;

bool dis_all_hw(const Student_info &s)
{
    return ((find(s.homework.begin(), s.homework.end(), 0))
         == s.homework.end());
}

double grade_aux(const Student_info& s)
{
    try {
        return grade(s);
    } catch (domain_error) {
        return grade(s.midterm, s.final, 0);
    }
}

double median_analysis(const vector<Student_info>& s)
{
    vector<double> grades;
    transform(s.begin(), s.end(),
            back_inserter(grades), grade_aux);
    return median(grades);
}

double average(const vector<double>& vec)
{
    if (vec.empty())
        return 0;
    return accumulate(vec.begin(), vec.end(), 0.0) / vec.size();
}

double average_grade(const Student_info& s)
{
    return grade(s.midterm, s.final, average(s.homework));
}

double average_analysis(const vector<Student_info>& students)
{
    vector<double> grades;

    transform(students.begin(), students.end(),
              back_inserter(grades), average_grade);
    return median(grades);
}

double optimistic_median(const Student_info& s)
{
    vector<double> nonzero;
    remove_copy(s.homework.begin(), s.homework.end(),
                back_inserter(nonzero), 0);

    if (nonzero.empty())
        return grade(s.midterm, s.final, 0);
    else
        return grade(s.midterm, s.final, median(nonzero));
}

double optimistic_median_analysis(const vector<Student_info>& students)
{
    vector<double> grades;

    transform(students.begin(), students.end(),
              back_inserter(grades), optimistic_median);
    return median(grades);
}


void write_analysis(ostream& out, const string& name,
                    double analysis(const vector<Student_info>&),
                    const vector<Student_info>& did,
                    const vector<Student_info>& didnt)
{
    cout << name << ": median(did) = " << analysis(did) <<
                    ", median(didnt) = " << analysis(didnt) << endl;
}

int main()
{
    vector<Student_info> did, didnt;
    Student_info student;
    string::size_type maxlen = 0;

    while (read(cin, student)) {
        if (dis_all_hw(student))
            did.push_back(student);
        else
            didnt.push_back(student);
    }
    if (did.empty()) {
        cout << "No student did all the homework!" << endl;
        return 1;
    }
    if (didnt.empty()) {
        cout << "Every student did all the homework!" << endl;
        return 1;
    }

    write_analysis(cout, "median", median_analysis, did, didnt);
    write_analysis(cout, "average", average_analysis, did, didnt);
    write_analysis(cout, "median of homework turned in",
                        optimistic_median_analysis, did, didnt);

    return 0;
}