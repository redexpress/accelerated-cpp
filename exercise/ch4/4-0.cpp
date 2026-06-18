#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <sstream>
#include <istream>
#include <string>
#include <vector>

struct Student_info {
    std::string name;
    double midterm, final;
    std::vector<double> homework;
};

double grade(double midterm, double final, double homework)
{
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

double median(std::vector<double> vec)
{

    auto size = vec.size();
    if (size == 0)
        throw std::domain_error("median of an empty vector");
    std::sort(vec.begin(), vec.end());

    auto mid = size/2;

    return size % 2 == 0 ? (vec[mid] + vec[mid-1]) / 2 : vec[mid];
}

double grade(double midterm, double final, const std::vector<double>& hw)
{
    return grade(midterm, final, median(hw));
}

double grade(const Student_info& s)
{
    return grade(s.midterm, s.final, s.homework);
}

std::istream& read_hw(std::istream& in, std::vector<double>& hw)
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

std::istream& read(std::istream& is, Student_info& s)
{
    is >> s.name >> s.midterm >> s.final;

    read_hw(is, s.homework);
    return is;
}

bool compare(const Student_info& x, const Student_info& y)
{
    return x.name < y.name;
}

int main()
{
    std::vector<Student_info> students;
    Student_info record;
    std::string::size_type maxlen = 0;

    std::istringstream input("Yang 80 90 85 90 78 92 88");
    while (read(input, record)) {
        maxlen = std::max(maxlen, record.name.size());
        students.push_back(record);
    }
    sort(students.begin(), students.end(), compare);

    for (std::vector<Student_info>::size_type i = 0;
        i != students.size(); ++i) {
        std::cout << std::setw(maxlen+1) << students[i].name;
        try {
            double final_grade = grade(students[i]);
            auto prec = std::cout.precision();
            std::cout << "\nYour final grade is " << std::setprecision(3)
                << final_grade << std::setprecision(prec) << std::endl;
        } catch (std::domain_error e) {
            std::cout << e.what();
        }
        std::cout << std::endl;
    }

    return 0;
}