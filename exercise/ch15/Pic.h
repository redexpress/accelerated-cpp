#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <string>

class Picture;

class Pic_base {
    friend std::ostream& operator<<(std::ostream&, const Picture&);
    friend class Frame_Pic;
    friend class HCat_Pic;
    friend class VCat_Pic;
    friend class String_Pic;

    [[nodiscard]] virtual size_t width() const = 0;
    [[nodiscard]] virtual size_t height() const = 0;
    virtual void display(std::ostream&, size_t, bool) const = 0;

protected:
    static void pad(std::ostream& os, size_t, size_t);
};

class Picture {
    friend std::ostream& operator<<(std::ostream&, const Picture&);
    friend Picture frame(const Picture&);
    friend Picture hcat(const Picture&, const Picture&);
    friend Picture vcat(const Picture&, const Picture&);

public:
    explicit Picture(const std::vector<std::string>& =
          std::vector<std::string>());
private:
    std::shared_ptr<Pic_base> p;
    Picture(Pic_base* ptr): p(ptr) { }
};

Picture frame(const Picture&);
Picture hcat(const Picture&, const Picture&);
Picture vcat(const Picture&, const Picture&);
std::ostream& operator<<(std::ostream&, const Picture&);

class Frame_Pic : public Pic_base {
    friend Picture frame(const Picture&);
    std::shared_ptr<Pic_base> p;
    Frame_Pic(const std::shared_ptr<Pic_base>& pic):p(pic) { }

    [[nodiscard]] size_t width() const;
    [[nodiscard]] size_t height() const;
    void display(std::ostream&, size_t, bool) const;
};

class VCat_Pic : public Pic_base {
    friend Picture vcat(const Picture&, const Picture&);
    std::shared_ptr<Pic_base> top, bottom;
    VCat_Pic(const std::shared_ptr<Pic_base>& t, const std::shared_ptr<Pic_base>& b):
           top(t), bottom(b) { }

    [[nodiscard]] size_t width() const
        { return std::max(top->width(), bottom->width()); }
    [[nodiscard]] size_t height() const
        { return top->height() + bottom->height(); }
    void display(std::ostream&, size_t, bool) const;
};

class HCat_Pic : public Pic_base {
    friend Picture hcat(const Picture&, const Picture&);
    std::shared_ptr<Pic_base> left, right;
    HCat_Pic(const std::shared_ptr<Pic_base>& l, const std::shared_ptr<Pic_base>& r):
          left(l), right(r) { }

    [[nodiscard]] size_t width() const { return left->width() + right->width(); }
    [[nodiscard]] size_t height() const { return std::max(left->height(), right->height()); }
    void display(std::ostream&, size_t, bool) const;
};

class String_Pic : public Pic_base {
    friend class Picture;
    std::vector<std::string> data;
    String_Pic(const std::vector<std::string>& v):data(v) { }

    [[nodiscard]] size_t width() const;
    [[nodiscard]] size_t height() const;
    void display(std::ostream&, size_t, bool) const;
};
