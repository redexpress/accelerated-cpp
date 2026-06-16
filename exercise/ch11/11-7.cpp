#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Vec.h"

double median(Vec<double> vec) {
    typedef Vec<double>::size_type vec_sz;

    vec_sz size = vec.size();
    if (size == 0)
        return 0.0;
    std::sort(vec.begin(), vec.end());

    vec_sz mid = size / 2;

    return size % 2 == 0 ? (vec[mid] + vec[mid - 1]) / 2 : vec[mid];
}

double grade(double midterm, double final, double homework) {
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

double grade(double midterm, double final, const Vec<double>& hw) {
    return grade(midterm, final, median(hw));
}

class Student_info {
public:
    Student_info();
    Student_info(std::istream&);
    std::string name() const { return n; }
    bool valid() const { return !homework.empty(); }
    double grade() const;
    std::istream& read(std::istream&);
private:
    std::string n;
    double midterm, final;
    Vec<double> homework;
};

bool compare(const Student_info&, const Student_info&);

Student_info::Student_info() : midterm(0), final(0) { }

Student_info::Student_info(std::istream& is) { read(is); }

double Student_info::grade() const {
    return ::grade(midterm, final, homework);
}

std::istream& read_hw(std::istream& in, Vec<double>& hw) {
    if (in) {
        hw.clear();
        double x;
        while (in >> x)
            hw.push_back(x);
        in.clear();
    }
    return in;
}

std::istream& Student_info::read(std::istream& in) {
    in >> n >> midterm >> final;
    read_hw(in, homework);
    return in;
}

bool compare(const Student_info& x, const Student_info& y) {
    return x.name() < y.name();
}

void grade_app() {
    Vec<Student_info> students;
    Student_info record;
    std::string::size_type maxlen = 0;

    std::string data = R"(Alice 85 90 75 80 95
Bob 70 80 60 65
Charlie 95 88 92 90 85 88
David 55 60 50 45
Eva 100 100 100 100 100
Frank 68 72 65 70 68
Grace 92 94 96 98
Henry 45 50 40 38
Ivy 88 85 90 92 87 91
Jack 79 82 75 80
Kevin 60 65 55 60 58
Lisa 98 97 99 100
Mona 50 55
NoHomeworkStudent 80 70
)";
    std::istringstream input(data);

    while (record.read(input)) {
        maxlen = std::max(maxlen, record.name().size());
        students.push_back(record);
    }
    std::sort(students.begin(), students.end(), compare);

    for (Vec<Student_info>::size_type i = 0; i != students.size(); ++i) {
        std::cout << std::setw(maxlen + 1) << students[i].name();
        try {
            double final_grade = students[i].grade();
            auto prec = std::cout.precision();
            std::cout << " Your final grade is " << std::setprecision(3)
                << final_grade << std::setprecision(prec) << std::endl;
        } catch (std::domain_error& e) {
            std::cout << e.what();
        }
        std::cout << std::endl;
    }
}

std::string::size_type width(const Vec<std::string>& v)
{
    std::string::size_type maxlen = 0;
    for (Vec<std::string>::size_type i = 0; i != v.size(); ++i)
        maxlen = std::max(maxlen, v[i].size());
    return maxlen;
}

Vec<std::string> frame(const Vec<std::string>& v)
{
    Vec<std::string> ret;
    std::string::size_type maxlen = width(v);
    std::string border(maxlen + 4, '*');
    ret.push_back(border);
    for (Vec<std::string>::size_type i = 0; i != v.size(); ++i) {
        ret.push_back("* " + v[i] +
            std::string(maxlen - v[i].size(), ' ') + " *");
    }
    ret.push_back(border);
    return ret;
}

Vec<std::string> vcat(const Vec<std::string>& top,
                const Vec<std::string>& bottom)
{
    Vec<std::string> ret = top;
    for (Vec<std::string>::const_iterator it = bottom.begin();
         it != bottom.end(); ++it)
        ret.push_back(*it);
    return ret;
}

Vec<std::string> hcat(const Vec<std::string>& left,
                const Vec<std::string>& right)
{
    Vec<std::string> ret;
    std::string::size_type width1 = width(left) + 1;
    Vec<std::string>::size_type i = 0, j = 0;
    while (i != left.size() || j != right.size()) {
        std::string s;
        if (i != left.size())
            s += left[i++];

        s += std::string(width1 - s.size(), ' ');

        if (j != right.size())
            s += right[j++];

        ret.push_back(s);
    }
    return ret;
}

void draw_app() {
    Vec<std::string> v1;
    v1.push_back("one");
    v1.push_back("two");
    v1.push_back("three");
    Vec<std::string> v2;
    v2.push_back("four");
    v2.push_back("five");
    v2.push_back("six");
    v2.push_back("seven");
    Vec<std::string> result = vcat(v1, v2);
    for (Vec<std::string>::size_type i = 0; i != result.size(); ++i) {
        std::cout << result[i] << ", ";
    }
    std::cout << std::endl;
    result = hcat(v1, frame(v2));
    for (Vec<std::string>::size_type i = 0; i != result.size(); ++i) {
        std::cout << result[i] << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    grade_app();
    std::cout << "----------------------------------\n";
    draw_app();
    return 0;
}
