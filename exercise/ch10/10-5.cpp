#include <iostream>
#include <string>
#include <cstddef>
#include <iterator>

class String_list {
    struct Node {
        std::string data;
        Node* next;
        Node* prev;
        Node(const std::string& s, Node* n = 0, Node* p = 0)
            : data(s), next(n), prev(p) {}
    };
    Node* head;
    std::size_t count;

public:
    class iterator {
        Node* p;
    public:
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef std::string                  value_type;
        typedef std::ptrdiff_t               difference_type;
        typedef std::string*                 pointer;
        typedef std::string&                 reference;

        iterator(Node* n = 0) : p(n) {}

        std::string& operator*()  const { return p->data; }
        std::string* operator->() const { return &p->data; }

        iterator& operator++()    { p = p->next; return *this; }
        iterator  operator++(int) { iterator t = *this; p = p->next; return t; }

        iterator& operator--()    { p = p->prev; return *this; }
        iterator  operator--(int) { iterator t = *this; p = p->prev; return t; }

        bool operator==(const iterator& o) const { return p == o.p; }
        bool operator!=(const iterator& o) const { return p != o.p; }
    };

    String_list() : head(0), count(0) {}
    ~String_list();

    void push_front(const std::string& s) {
        Node* n = new Node(s, head, 0);
        if (head) head->prev = n;
        head = n;
        ++count;
    }
    void push_back(const std::string& s);
    std::size_t size() const         { return count; }
    bool        empty() const        { return count == 0; }

    std::string& front()             { return head->data; }
    const std::string& front() const { return head->data; }

    iterator begin()                 { return iterator(head); }
    iterator end()                   { return iterator(0); }
};

String_list::~String_list() {
    while (head) {
        Node* p = head;
        head = head->next;
        delete p;
    }
}

void String_list::push_back(const std::string& s) {
    Node* n = new Node(s, 0, 0);
    if (!head) {
        head = n;
    } else {
        Node* tail = head;
        while (tail->next) tail = tail->next;
        tail->next = n;
        n->prev    = tail;
    }
    ++count;
}

int main() {
    String_list lst;
    lst.push_back("hello");
    lst.push_back("world");
    lst.push_back("!");
    lst.push_front(">>>");

    std::cout << "forward:\n";
    for (String_list::iterator it = lst.begin(); it != lst.end(); ++it)
        std::cout << "  " << *it << "\n";

    String_list::iterator last = lst.begin();
    for (String_list::iterator it = lst.begin(); it != lst.end(); ++it)
        last = it;

    std::cout << "backward (-- from last):\n";
    for (String_list::iterator it = last; ; --it) {
        std::cout << "  " << *it << "\n";
        if (it == lst.begin()) break;
    }

    return 0;
}
