#include "Student_info.h"
#include <vector>
#include "grade.h"

using std::istream;
using std::vector;

Student_info::Student_info():midterm(0), final(0) { }

Student_info::Student_info(std::istream &is) { read(is); }

double Student_info::grade() const
{
    return ::grade(midterm, final, homework);
}

istream& read_hw(istream& in, vector<double>& hw)
{
    if (in) {
        hw.clear();
        double x;
        while (in >> x)
            hw.push_back(x);
        in.clear();
    }
    return in;
}

std::istream& Student_info::read(std::istream& in)
{
    in >> n >> midterm >> final;
    read_hw(in, homework);
    return in;
}

bool compare(const Student_info& x, const Student_info& y)
{
    return x.name() < y.name();
}
