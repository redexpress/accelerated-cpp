#pragma once

#include <algorithm>
#include <cstddef>
#include <memory>
#include <utility>

template <class T> class Vec {
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = T*;
    using const_iterator = const T*;
    using iterator_category = std::contiguous_iterator_tag;

    Vec() = default;
    explicit Vec(size_type n, const T& t = T()) { create(n, t); }

    Vec(const Vec& v) { create(v.begin(), v.end()); }
    Vec(Vec&& other) noexcept
        : data(other.data), avail(other.avail), limit(other.limit) {
        other.data = other.avail = other.limit = nullptr;
    }
    Vec& operator=(const Vec&);
    Vec& operator=(Vec&& rhs) noexcept;
    ~Vec() noexcept { uncreate(); }

    T& operator[](size_type i) { return data[i]; }
    const T& operator[](size_type i) const { return data[i]; }

    template <class U>
    void push_back(U&& u) {
        emplace_back(std::forward<U>(u));
    }
    template <class... Args>
    void emplace_back(Args&&... args) {
        if (avail == limit)
            grow();
        traits::construct(alloc, avail++, std::forward<Args>(args)...);
    }

    [[nodiscard]]
    size_type size() const noexcept { return avail - data; }
    [[nodiscard]]
    size_type capacity() const noexcept { return limit - data; }

    iterator begin() noexcept { return data; }
    const_iterator begin() const noexcept { return data; }

    iterator end() noexcept { return avail; }
    const_iterator end() const noexcept { return avail; }

    void clear() { uncreate(); }
    [[nodiscard]]
    bool empty() const noexcept { return data == avail; }

    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);

    void reserve(size_type n) {
        if (n <= capacity()) return;
        reallocate(n);
    }

private:
    iterator data{};
    iterator avail{};
    iterator limit{};

    std::allocator<T> alloc;
    using traits = std::allocator_traits<std::allocator<T>>;

    void create(size_type, const T&);
    void create(const_iterator, const_iterator);

    void uncreate();

    void grow();
    void reallocate(size_type new_capacity);
};

template <class T> void Vec<T>::create(size_type n, const T& val) {
    data = alloc.allocate(n);
    limit = avail = data + n;
    std::uninitialized_fill(data, limit, val);
}

template <class T>
void Vec<T>::create(const_iterator i, const_iterator j) {
    data = alloc.allocate(j - i);
    limit = avail = std::uninitialized_copy(i, j, data);
}

template <class T> void Vec<T>::uncreate() {
    if (data) {
        std::destroy(data, avail);
        traits::deallocate(alloc, data, limit - data);
    }
    data = limit = avail = nullptr;
}

template <class T> void Vec<T>::reallocate(size_type new_capacity) {
    iterator new_data = alloc.allocate(new_capacity);
    iterator new_avail = new_data;
    try {
        new_avail = std::uninitialized_move(data, avail, new_data);
    } catch (...) {
        std::destroy(new_data, new_avail);
        traits::deallocate(alloc, new_data, new_capacity);
        throw;
    }
    uncreate();
    data = new_data;
    avail = new_avail;
    limit = data + new_capacity;
}

template <class T> void Vec<T>::grow() {
    reallocate(std::max<size_type>(capacity() * 2, 1));
}

template <class T> Vec<T>& Vec<T>::operator=(const Vec& rhs) {
    if (&rhs != this) {
        uncreate();
        create(rhs.begin(), rhs.end());
    }
    return *this;
}

template <class T> Vec<T>& Vec<T>::operator=(Vec&& rhs) noexcept {
    if (&rhs != this) {
        uncreate();
        data = rhs.data;
        avail = rhs.avail;
        limit = rhs.limit;
        rhs.data = rhs.avail = rhs.limit = nullptr;
    }
    return *this;
}

template <class T>
typename Vec<T>::iterator Vec<T>::erase(const_iterator pos) {
    return erase(pos, pos + 1);
}

template <class T>
typename Vec<T>::iterator Vec<T>::erase(const_iterator first, const_iterator last) {
    if (first == last) return iterator(const_cast<iterator>(first));

    iterator cut = const_cast<iterator>(first);
    iterator new_end = std::move(cut + (last - first), avail, cut);
    std::destroy(new_end, avail);
    avail = new_end;
    return cut;
}
