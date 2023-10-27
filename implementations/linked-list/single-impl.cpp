#include <bits/stdc++.h>
using namespace std;

// linked list is a collection of nodes in a linear fashion that each have two
// elements, the element and a pointer to the next node in the list.
// Each node itself is a pointer
// the first pointer is called the head node and the last is called the tail
// node

class StringNode {
   private:
    string ele;
    StringNode* next;

    friend class StringLinkedList;
};

class StringLinkedList {
   public:
    StringLinkedList();
    ~StringLinkedList();
    bool empty() const;
    const string& front() const;
    void addFront(const string& e);
    void removeFront();

   private:
    StringNode* head;
};

StringLinkedList::StringLinkedList() : head(nullptr) {}
StringLinkedList::~StringLinkedList() {
    while (!empty()) removeFront();
}

bool StringLinkedList::empty() const { return head == nullptr; }

const string& StringLinkedList::front() const { return head->ele; }

void StringLinkedList::addFront(const string& ele) {
    StringNode* v = new StringNode;
    v->ele = ele;
    v->next = head;
    head = v;
}

void StringLinkedList::removeFront() {
    StringNode* v = head;
    head = head->next;
    delete v;
}

int main() { return 0; }