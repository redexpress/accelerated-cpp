#ifndef GUARD_Student_info
#define GUARD_Student_info

#include <string>
#include <vector>
#include <istream>

class Student_info {
public:
    Student_info();
    Student_info(std::istream&);
    std::string name() const {return n;}
    bool valid() const { return !homework.empty(); }
    double grade() const;
    std::istream& read(std::istream&);
private:
    std::string n;
    double midterm, final;
    std::vector<double> homework;
};

bool compare(const Student_info&, const Student_info&);
#endif
