#include "Core.h"
#include <string>
#include <vector>
#include "grade.h"
#include "read_hw.h"

using std::string;
using std::istream;
using std::vector;
using std::min;

string Core::name() const {return n; }

double Core::grade() const
{
    return ::grade(midterm, final, homework);
}

istream& Core::read_common(istream& in)
{
    in>>n>>midterm>>final;
    return in;
}

istream& Core::read(istream& in)
{
    read_common(in);
    read_hw(in, homework);
    return in;
}

bool compare(const Core& c1, const Core& c2)
{
    return c1.name()<c2.name();
}

bool compare_core_ptrs(const Core* cp1, const Core* cp2)
{
    return compare(*cp1, *cp2);
}

std::istream& Grad::read(std::istream& in)
{
    Core::read_common(in);
    in>>thesis;
    read_hw(in, Core::homework);
    return in;
}

double Grad::grade() const
{
    return min(Core::grade(), thesis);
}