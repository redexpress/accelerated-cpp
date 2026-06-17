#include "Pic.h"

Picture frame(const Picture& pic) {
	return new Frame_Pic(pic.p);
}

Picture hcat(const Picture& l, const Picture& r) {
	return new HCat_Pic(l.p, r.p);
}

Picture vcat(const Picture& t, const Picture& b) {
	return new VCat_Pic(t.p, b.p);
}

Picture::Picture(const std::vector<std::string>& v): p(new String_Pic(v)) { }

std::ostream& operator<<(std::ostream& os, const Picture& picture) {
	const size_t ht = picture.p->height();
	for (size_t i = 0; i != ht; ++i) {
		picture.p->display(os, i, false);
		os << std::endl;
	}
	return os;
}

size_t String_Pic::width() const {
	size_t n = 0;
	for (size_t i = 0; i != data.size(); ++i)
		n = std::max(n, data[i].size());
	return n;
}

size_t String_Pic::height() const {
    return data.size();
}

void String_Pic::display(std::ostream& os, size_t row, bool do_pad) const {
	size_t start = 0;

	if (row < height()) {
		os << data[row];
		start = data[row].size();
	}
	if (do_pad)
		pad(os, start, width());
}

void VCat_Pic::display(std::ostream& os, size_t row, bool do_pad) const {
	size_t w = 0;
	if (row < top->height()) {
		top->display(os, row, do_pad);
		w = top->width();
	} else if (row < height()) {
		bottom->display(os, row - top->height(), do_pad);
		w = bottom->width();
	}
	if (do_pad)
		pad(os, w, width());
}

void HCat_Pic::display(std::ostream& os, size_t row, bool do_pad) const {
	left->display(os, row, do_pad || row < right->height());
	right->display(os, row, do_pad);
}

void Frame_Pic::display(std::ostream& os, size_t row, bool do_pad) const {
	if (row >= height()) {
		if (do_pad)
			pad(os, 0, width());
	} else {
		if (row == 0 || row == height() - 1) {
			os << std::string(width(), '*');
		} else if (row == 1 || row == height() - 2) {
			os << "*";
			pad(os, 1, width() - 1);
			os << "*";
		} else {
			os << "* ";
			p->display(os, row - 2, true);
			os << " *";
		}
	}
}

size_t Frame_Pic::width() const {
    return p->width() + 4;
}

size_t Frame_Pic::height() const {
    return p->height() + 4;
}

void Pic_base::pad(std::ostream& os, size_t beg, size_t end) {
	while (beg != end) {
		os << " ";
		++beg;
	}
}
