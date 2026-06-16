#ifndef GUARD_Str
#define GUARD_Str

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <cctype>
#include <iostream>
#include <istream>
#include <iterator>
#include <stdexcept>

class Str {
    friend std::istream& operator>>(std::istream&, Str&);
    friend std::istream& getline(std::istream&, Str&);
    friend std::istream& getline(std::istream&, Str&, char);
    friend Str operator+(const char*, const Str&);
public:
    typedef size_t size_type;

    class const_iterator;
    class iterator {
        char* p;
        friend class const_iterator;
    public:
        typedef std::random_access_iterator_tag iterator_category;
        typedef char                          value_type;
        typedef std::ptrdiff_t                difference_type;
        typedef char*                         pointer;
        typedef char&                         reference;

        iterator() : p(0) {}
        explicit iterator(char* x) : p(x) {}

        reference  operator*()  const { return *p; }
        pointer    operator->() const { return  p; }
        reference  operator[](difference_type n) const { return p[n]; }

        iterator& operator++()    { ++p; return *this; }
        iterator  operator++(int) { iterator t = *this; ++p; return t; }
        iterator& operator--()    { --p; return *this; }
        iterator  operator--(int) { iterator t = *this; --p; return t; }

        iterator& operator+=(difference_type n) { p += n; return *this; }
        iterator& operator-=(difference_type n) { p -= n; return *this; }
        friend iterator operator+(iterator it, difference_type n) { it += n; return it; }
        friend iterator operator+(difference_type n, iterator it) { it += n; return it; }
        friend iterator operator-(iterator it, difference_type n) { it -= n; return it; }
        friend difference_type operator-(const iterator& a, const iterator& b) { return a.p - b.p; }

        friend bool operator==(const iterator& a, const iterator& b) { return a.p == b.p; }
        friend bool operator!=(const iterator& a, const iterator& b) { return a.p != b.p; }
        friend bool operator< (const iterator& a, const iterator& b) { return a.p <  b.p; }
        friend bool operator<=(const iterator& a, const iterator& b) { return a.p <= b.p; }
        friend bool operator> (const iterator& a, const iterator& b) { return a.p >  b.p; }
        friend bool operator>=(const iterator& a, const iterator& b) { return a.p >= b.p; }
    };

    class const_iterator {
        const char* p;
    public:
        typedef std::random_access_iterator_tag iterator_category;
        typedef char                          value_type;
        typedef std::ptrdiff_t                difference_type;
        typedef const char*                   pointer;
        typedef const char&                   reference;

        const_iterator() : p(0) {}
        const_iterator(const char* x) : p(x) {}
        const_iterator(iterator it) : p(it.p) {}

        reference  operator*()  const { return *p; }
        pointer    operator->() const { return  p; }
        reference  operator[](difference_type n) const { return p[n]; }

        const_iterator& operator++()    { ++p; return *this; }
        const_iterator  operator++(int) { const_iterator t = *this; ++p; return t; }
        const_iterator& operator--()    { --p; return *this; }
        const_iterator  operator--(int) { const_iterator t = *this; --p; return t; }

        const_iterator& operator+=(difference_type n) { p += n; return *this; }
        const_iterator& operator-=(difference_type n) { p -= n; return *this; }
        friend const_iterator operator+(const_iterator it, difference_type n) { it += n; return it; }
        friend const_iterator operator+(difference_type n, const_iterator it) { it += n; return it; }
        friend const_iterator operator-(const_iterator it, difference_type n) { it -= n; return it; }
        friend difference_type operator-(const const_iterator& a, const const_iterator& b) { return a.p - b.p; }

        friend bool operator==(const const_iterator& a, const const_iterator& b) { return a.p == b.p; }
        friend bool operator!=(const const_iterator& a, const const_iterator& b) { return a.p != b.p; }
        friend bool operator< (const const_iterator& a, const const_iterator& b) { return a.p <  b.p; }
        friend bool operator<=(const const_iterator& a, const const_iterator& b) { return a.p <= b.p; }
        friend bool operator> (const const_iterator& a, const const_iterator& b) { return a.p >  b.p; }
        friend bool operator>=(const const_iterator& a, const const_iterator& b) { return a.p >= b.p; }
    };

    Str& operator+=(const Str& s) {
        size_type old = len;
        grow_to(len + s.len);
        std::copy(s.d, s.d + s.len, d + old);
        d[len] = '\0';
        return *this;
    }
    Str& operator+=(const char* s) {
        size_type old = len;
        size_type n = std::strlen(s);
        grow_to(len + n);
        std::copy(s, s + n, d + old);
        d[len] = '\0';
        return *this;
    }

    Str() : d(new char[1]), len(0) { d[0] = '\0'; }
    Str(size_type n, char c) : d(new char[n + 1]), len(n) { std::fill(d, d + n, c); d[n] = '\0'; }
    Str(const char* cp) : d(new char[std::strlen(cp) + 1]), len(std::strlen(cp)) { std::copy(cp, cp + len, d); d[len] = '\0'; }
    template <class In> Str(In i, In j) {
        len = j - i;
        d = new char[len + 1];
        std::copy(i, j, d);
        d[len] = '\0';
    }

    Str(const Str& s) : d(new char[s.len + 1]), len(s.len) { std::copy(s.d, s.d + len, d); d[len] = '\0'; }
    Str& operator=(const Str& s) {
        if (this != &s) {
            char* nd = new char[s.len + 1];
            std::copy(s.d, s.d + s.len, nd);
            nd[s.len] = '\0';
            delete[] d;
            d = nd;
            len = s.len;
        }
        return *this;
    }
    ~Str() { delete[] d; }

    char& operator[](size_type i) { return d[i]; }
    const char& operator[](size_type i) const { return d[i]; }
    size_type size() const { return len; }
    explicit operator bool() const noexcept { return len != 0; }

    iterator       begin()       { return iterator(d); }
    const_iterator begin() const { return const_iterator(d); }
    iterator       end()         { return iterator(d + len); }
    const_iterator end()   const { return const_iterator(d + len); }

    const char* c_str() const { return d; }
    const char* data()  const { return d; }

    size_type copy(char* dest, size_type count, size_type pos = 0) const {
        if (pos > len)
            throw std::out_of_range("Str::copy");
        size_type n = (count < len - pos) ? count : (len - pos);
        std::copy(d + pos, d + pos + n, dest);
        return n;
    }

private:
    char* d;
    size_type len;

    void grow_to(size_type n) {
        char* nd = new char[n + 1];
        std::copy(d, d + len, nd);
        nd[len] = '\0';
        delete[] d;
        d = nd;
        len = n;
    }
    void push_one(char c) {
        grow_to(len + 1);
        d[len - 1] = c;
        d[len] = '\0';
    }
};

std::ostream& operator<<(std::ostream&, const Str&);
std::istream& operator>>(std::istream&, Str&);
std::istream& getline(std::istream&, Str&);
std::istream& getline(std::istream&, Str&, char);

Str operator+(const Str&, const Str&);
Str operator+(const Str&, const char*);
Str operator+(const char*, const Str&);

int compare(const Str&, const Str&);
bool operator<(const Str&, const Str&);
bool operator>(const Str&, const Str&);
bool operator<=(const Str&, const Str&);
bool operator>=(const Str&, const Str&);
bool operator==(const Str&, const Str&);
bool operator!=(const Str&, const Str&);

inline std::ostream& operator<<(std::ostream& os, const Str& s) {
    std::copy(s.begin(), s.end(), std::ostream_iterator<char>(os));
    return os;
}

inline std::istream& operator>>(std::istream& is, Str& s) {
    s.d[0] = '\0';
    s.len = 0;

    char c;
    while (is.get(c) && std::isspace(static_cast<unsigned char>(c)))
        ;

    if (is) {
        do {
            s.push_one(c);
        } while (is.get(c) && !std::isspace(static_cast<unsigned char>(c)));

        if (is)
            is.unget();
    }
    return is;
}

inline std::istream& getline(std::istream& is, Str& s) {
    return getline(is, s, '\n');
}

inline std::istream& getline(std::istream& is, Str& s, char delim) {
    s.d[0] = '\0';
    s.len = 0;

    char c;
    while (is.get(c) && c != delim)
        s.push_one(c);
    return is;
}

inline Str operator+(const Str& s, const Str& t) { Str r = s; r += t; return r; }
inline Str operator+(const Str& s, const char* t) { Str r = s; r += t; return r; }

inline Str operator+(const char* literal, const Str& s) {
    Str::size_type n1 = std::strlen(literal);
    Str::size_type n2 = s.size();
    Str r;
    r.grow_to(n1 + n2);
    std::copy(literal, literal + n1, r.d);
    std::copy(s.d, s.d + n2, r.d + n1);
    r.d[n1 + n2] = '\0';
    return r;
}

inline int compare(const Str& s, const Str& t) {
    return std::strcmp(s.c_str(), t.c_str());
}

inline bool operator<(const Str& lhs, const Str& rhs)  { return compare(lhs, rhs) <  0; }
inline bool operator>(const Str& lhs, const Str& rhs)  { return compare(lhs, rhs) >  0; }
inline bool operator<=(const Str& lhs, const Str& rhs) { return compare(lhs, rhs) <= 0; }
inline bool operator>=(const Str& lhs, const Str& rhs) { return compare(lhs, rhs) >= 0; }
inline bool operator==(const Str& lhs, const Str& rhs) { return compare(lhs, rhs) == 0; }
inline bool operator!=(const Str& lhs, const Str& rhs) { return compare(lhs, rhs) != 0; }

#endif
