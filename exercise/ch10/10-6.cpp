#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <cstddef>
#include <string_view>

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

String_list split(const std::string& s) {
    String_list ret;
    auto i = s.begin();
    while (i != s.end()) {
        i = std::find_if(i, s.end(), [](unsigned char c) { return !std::isspace(c); });
        auto j = std::find_if(i, s.end(), [](unsigned char c) { return  std::isspace(c); });
        if (i != s.end())
            ret.push_back(std::string(i, j));
        i = j;
    }
    return ret;
}

int main() {
    String_list lst = split("one two three");
    std::cout << "size = " << lst.size() << "\n";
    std::cout << "front = " << lst.front() << "\n";

    for (String_list::iterator it = lst.begin(); it != lst.end(); ++it)
        std::cout << *it << "\n";

    return 0;
}
