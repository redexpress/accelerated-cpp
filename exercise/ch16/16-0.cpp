#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Core.h"
#include "Pic.h"

Picture histogram(const std::vector<Student_info>& students) {
    Picture names;
    Picture grades;
    for (auto it = students.begin(); it != students.end(); ++it) {
        names = vcat(names, std::vector<std::string>(1, it->name()));
        grades = vcat(grades,
            std::vector<std::string>(1, " " + std::string(it->grade()/2, '=')));
        }
    return hcat(names, grades);
}

int main() {
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

    std::vector<Student_info> students;
    Student_info s;
    while (s.read(input))
        students.push_back(s);
    sort(students.begin(), students.end(), Student_info::compare);
    std::cout << frame(histogram(students)) << std::endl;
}

