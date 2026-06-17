#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <istream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Core.h"
#include "Ref_handle.h"

bool compare_Core_handles(const Ref_handle<Core>& lhs, const Ref_handle<Core>& rhs) {
    return compare(*lhs, *rhs);
}

bool compare_shared_Cores(const std::shared_ptr<Core>& lhs, const std::shared_ptr<Core>& rhs) {
    return compare(*lhs, *rhs);
}

void grade_ref_handle_version() {
    std::vector<Ref_handle<Core>> students;
    Ref_handle<Core> record;
    char ch;
    std::string::size_type maxlen = 0;

    std::string data = R"(
U Alice 85 90 75 80 95
U Bob 70 80 60 65
G Charlie 95 88 92 85 88 90
U David 55 60 50 45
G Eva 100 100 100 100 100 100
U Frank 68 72 65 70 68
U Grace 92 94 96 98
G Henry 45 50 40 38 42
U Ivy 88 85 90 92 87 91
U Jack 79 82 75 80
G Kevin 60 65 55 60 58
U Lisa 98 97 99 100
U Mona 50 55 60 65
G NoThesisStudent 80 70
)";
    std::istringstream input(data);

    while (input>>ch) {
        if (ch=='U')
            record = new Core;
        else
            record = new Grad;
        record->read(input);
        maxlen = std::max(maxlen, record->name().size());
        students.push_back(record);
    }

    sort(students.begin(), students.end(), compare_Core_handles);

    for (auto i = 0; i != students.size(); ++i) {
        std::cout << std::setw(maxlen + 1) << students[i]->name() << ' ';
        try {
            double final_grade = students[i]->grade();
            std::streamsize prec = std::cout.precision();
            std::cout << std::setprecision(3) << final_grade
                 << std::setprecision(prec) << std::endl;
        } catch (std::domain_error e) {
            std::cout << e.what() << std::endl;
        }
    }
}

void grade_shared_ptr_version() {
    std::vector<std::shared_ptr<Core>> students;
    std::shared_ptr<Core> record;
    char ch;
    std::string::size_type maxlen = 0;

    std::string data = R"(
U Alice 85 90 75 80 95
U Bob 70 80 60 65
G Charlie 95 88 92 85 88 90
U David 55 60 50 45
G Eva 100 100 100 100 100 100
U Frank 68 72 65 70 68
U Grace 92 94 96 98
G Henry 45 50 40 38 42
U Ivy 88 85 90 92 87 91
U Jack 79 82 75 80
G Kevin 60 65 55 60 58
U Lisa 98 97 99 100
U Mona 50 55 60 65
G NoThesisStudent 80 70
)";
    std::istringstream input(data);

    while (input>>ch) {
        if (ch=='U')
            record = std::make_shared<Core>();
        else
            record = std::make_shared<Grad>();
        record->read(input);
        maxlen = std::max(maxlen, record->name().size());
        students.push_back(record);
    }

    sort(students.begin(), students.end(), compare_shared_Cores);

    for (std::vector<std::shared_ptr<Core>>::size_type i = 0; i != students.size(); ++i) {
        std::cout << std::setw(maxlen + 1) << students[i]->name() << ' ';
        try {
            double final_grade = students[i]->grade();
            std::streamsize prec = std::cout.precision();
            std::cout << std::setprecision(3) << final_grade
                 << std::setprecision(prec) << std::endl;
        } catch (std::domain_error e) {
            std::cout << e.what() << std::endl;
        }
    }
}

int main() {
    std::cout << "==== Ref_handle version ====" << std::endl;
    grade_ref_handle_version();
    std::cout << "==== shared_ptr version ====" << std::endl;
    grade_shared_ptr_version();
    return 0;
}