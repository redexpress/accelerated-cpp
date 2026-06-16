#pragma once

#include <cstddef>
#include <utility>

template <class T>
class List {
    struct Node {
        T value;
        Node* prev;
        Node* next;

        template <class... Args>
        Node(Node* p, Node* n, Args&&... args)
            : value(std::forward<Args>(args)...), prev(p), next(n) {}
    };

public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using const_reference = const T&;

    class iterator {
    public:
        iterator() = default;
        explicit iterator(Node* p) : ptr(p) {}

        reference operator*() const { return ptr->value; }
        bool operator==(const iterator&) const = default;

    private:
        Node* ptr{};
        friend class List;
    };

    using const_iterator = iterator;

    List() = default;

    List(const List& rhs) {
        for (const auto& v : rhs)
            push_back(v);
    }

    List(List&& rhs) noexcept
        : head(rhs.head), tail(rhs.tail), sz(rhs.sz) {
        rhs.head = rhs.tail = nullptr;
        rhs.sz = 0;
    }

    List& operator=(const List&);
    List& operator=(List&&) noexcept;
    ~List() { clear(); }

    template <class U>
    void push_back(U&& value) {
        Node* node = new Node(tail, nullptr, std::forward<U>(value));

        if (tail)
            tail->next = node;
        else
            head = node;

        tail = node;
        ++sz;
    }

    iterator erase(iterator pos);

    void clear() {
        while (head) {
            Node* next = head->next;
            delete head;
            head = next;
        }

        tail = nullptr;
        sz = 0;
    }

    [[nodiscard]]
    bool empty() const noexcept { return sz == 0; }

    [[nodiscard]]
    size_type size() const noexcept { return sz; }

    iterator begin() noexcept { return iterator(head); }
    iterator end() noexcept { return iterator(nullptr); }

    const_iterator begin() const noexcept { return const_iterator(head); }
    const_iterator end() const noexcept { return const_iterator(nullptr); }

private:
    Node* head{};
    Node* tail{};
    size_type sz{};
};

template <class T>
List<T>& List<T>::operator=(const List& rhs) {
    if (this != &rhs) {
        clear();
        for (const auto& v : rhs)
            push_back(v);
    }
    return *this;
}

template <class T>
List<T>& List<T>::operator=(List&& rhs) noexcept {
    if (this != &rhs) {
        clear();

        head = rhs.head;
        tail = rhs.tail;
        sz = rhs.sz;

        rhs.head = rhs.tail = nullptr;
        rhs.sz = 0;
    }

    return *this;
}

template <class T>
typename List<T>::iterator List<T>::erase(iterator pos) {
    Node* node = pos.ptr;
    if (!node) return end();

    Node* next = node->next;

    if (node->prev)
        node->prev->next = node->next;
    else
        head = node->next;

    if (node->next)
        node->next->prev = node->prev;
    else
        tail = node->prev;

    delete node;
    --sz;

    return iterator(next);
}