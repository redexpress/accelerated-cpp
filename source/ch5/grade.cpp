#include "grade.h"
#include "median.h"
#include <list>

using std::vector;
using std::list;

bool fgread(const Student_info& s)
{
    return grade(s) < 60;
}

double grade(double midterm, double final, double homework)
{
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

double grade(double midterm, double final, const vector<double>& hw)
{
    return grade(midterm, final, median(hw));
}

double grade(const Student_info& s)
{
    return grade(s.midterm, s.final, s.homework);
}

// version1
vector<Student_info> extract_fails1(vector<Student_info>& students) {
    vector<Student_info> pass, fail;
    for (vector<Student_info>::size_type i = 0;
         i != students.size(); i++)
        if (fgread(students[i]))
            pass.push_back(students[i]);
        else
            fail.push_back(students[i]);
    students = pass;
    return fail;
}

// version2
vector<Student_info> extract_fails2(vector<Student_info>& students) {
    vector<Student_info> fail;
    vector<Student_info>::size_type i = 0;
    while (i != students.size()) {
        if (fgread(students[i])) {
            fail.push_back(students[i]);
            students.erase(students.begin() + i);
        } else
            ++i;
    }
    return fail;
}

// version3
vector<Student_info> extract_fails3(vector<Student_info>& students) {
    vector<Student_info> fail;
    vector<Student_info>::iterator iter = students.begin();
    while (iter != students.end()) {
        if (fgread(*iter)) {
            fail.push_back(*iter);
            iter = students.erase(iter);
        } else
            ++iter;
    }
    return fail;
}

// version4
list<Student_info> extract_fails(list<Student_info>& students) {
    list<Student_info> fail;
    list<Student_info>::iterator iter = students.begin();
    while (iter != students.end()) {
        if (fgread(*iter)) {
            fail.push_back(*iter);
            iter = students.erase(iter);
        } else
            ++iter;
    }
    return fail;
}