#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Core.h"

int main()
{
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
    std::sort(students.begin(), students.end(), Student_info::compare);

    for (std::vector<Student_info>::size_type i = 0;
        i != students.size(); ++i) {
        std::cout << std::setw(maxlen+1) << students[i].name();
        try {
            double final_grade = students[i].grade();
            std::streamsize prec = std::cout.precision();
            std::cout << " Your final grade is " << std::setprecision(3)
                << final_grade << std::setprecision(prec) << std::endl;
        } catch (std::domain_error e) {
            std::cout << e.what();
        }
        std::cout << std::endl;
    }

    return 0;
}