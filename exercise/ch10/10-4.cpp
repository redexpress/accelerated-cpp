#include <iostream>
#include <string>
#include <cstddef>

class String_list {
    struct Node {
        std::string data;
        Node* next;
        Node(const std::string& s, Node* n = 0) : data(s), next(n) {}
    };
    Node* head;
    std::size_t count;

public:
    class iterator {
        Node* p;
    public:
        iterator(Node* n = 0) : p(n) {}
        std::string& operator*()  const { return p->data; }
        std::string* operator->() const { return &p->data; }
        iterator& operator++()        { p = p->next; return *this; }
        iterator  operator++(int)     { iterator t = *this; p = p->next; return t; }
        bool operator==(const iterator& o) const { return p == o.p; }
        bool operator!=(const iterator& o) const { return p != o.p; }
    };

    String_list() : head(0), count(0) {}
    ~String_list();

    void push_front(const std::string& s) {
        head = new Node(s, head);
        ++count;
    }
    void push_back(const std::string& s);
    std::size_t size() const          { return count; }
    std::string& front()              { return head->data; }
    const std::string& front() const  { return head->data; }

    iterator begin()                  { return iterator(head); }
    iterator end()                    { return iterator(0);   }
};

String_list::~String_list() {
    while (head) {
        Node* p = head;
        head = head->next;
        delete p;
    }
}

void String_list::push_back(const std::string& s) {
    Node** p = &head;
    while (*p) p = &(*p)->next;
    *p = new Node(s, 0);
    ++count;
}

int main() {
    String_list lst;
    lst.push_back("hello");
    lst.push_back("world");
    lst.push_front(">>>");

    std::cout << "size = " << lst.size() << "\n";
    std::cout << "front = " << lst.front() << "\n";

    for (String_list::iterator it = lst.begin(); it != lst.end(); ++it)
        std::cout << *it << "\n";

    return 0;
}
