#ifndef GUARD_Core
#define GUARD_Core

#include <istream>
#include <vector>

class Student_info;


class Core {
    friend class Student_info;
public:
    Core():midterm(0), final(0) {}
    Core(std::istream& is) {read(is);}
    std::string name() const;
    virtual std::istream& read(std::istream&);
    virtual double grade() const;
protected:
    std::istream& read_common(std::istream&);
    double midterm, final;
    std::vector<double> homework;

    virtual Core* clone() const { return new Core(*this); }
private:
    std::string n;
};

bool compare(const Core&, const Core&);
bool compare_core_ptrs(const Core*, const Core*);


class Grad : public Core {
public:
    Grad():thesis(0){}
    Grad(std::istream& is){ read(is); }
    double grade() const;
    std::istream& read(std::istream& is);
protected:
    Grad* clone() const { return new Grad(*this); }
private:
    double thesis;
};


class Student_info {
public:
    Student_info(): cp(0) { }
    Student_info(std::istream& is): cp(0) { read(is); }
    Student_info(const Student_info&);
    Student_info& operator=(const Student_info&);
    ~Student_info() { delete cp; }

    std::istream& read(std::istream&);

    std::string name() const {
        if (cp) return cp->name();
        else throw std::runtime_error("uninitialized Student");
    }
    double grade() const {
        if (cp) return cp->grade();
        else throw std::runtime_error("uninitialized Student");
    }

    static bool compare(const Student_info& s1,
                        const Student_info& s2) {
        return s1.name() < s2.name();
    }

private:
    Core* cp;
};

#endif
