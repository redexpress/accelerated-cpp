#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "median.h"

double grade(double midterm, double final, double homework) {
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

double grade(double midterm, double final, const std::vector<double>& hw) {
    if (hw.empty()) return 0.0;
    return grade(midterm, final, median(hw));
}

class Student_info {
public:
    Student_info();
    Student_info(std::istream&);
    std::string name() const {return n;}
    bool valid() const { return !homework.empty(); }
    std::istream& read(std::istream&);
    double grade() const { return final_grade; }
private:
    std::string n;
    double midterm, final;
    std::vector<double> homework;
    double final_grade;
};

bool compare(const Student_info&, const Student_info&);

Student_info::Student_info():midterm(0), final(0), final_grade(0) { }

Student_info::Student_info(std::istream &is) { read(is); }

std::istream& read_hw(std::istream& in, std::vector<double>& hw) {
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
    final_grade = ::grade(midterm, final, homework);
    return in;
}

bool compare(const Student_info& x, const Student_info& y) {
    return x.name() < y.name();
}

int main() {
    std::vector<Student_info> students;
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
    sort(students.begin(), students.end(), compare);

    for (auto i = 0; i != students.size(); ++i) {
        std::cout << std::setw(maxlen+1) << students[i].name();
        try {
            double final_grade = students[i].grade();
            auto prec = std::cout.precision();
            std::cout << " Your final grade is " << std::setprecision(3)
                << final_grade << std::setprecision(prec) << std::endl;
        } catch (std::domain_error e) {
            std::cout << e.what();
        }
        std::cout << std::endl;
    }

    return 0;
}
