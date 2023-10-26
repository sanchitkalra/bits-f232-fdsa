#include <bits/stdc++.h>
using namespace std;

// a doubly linked list node has three elements:
// 1. the element being stored
// 2. a next pointer
// 3. a prev pointer

// the list itself tracks two pointers: head and tail
// for implementation simplicity, we keep them as dummy nodes

class DNode {
   private:
    string ele;
    DNode* prev;
    DNode* next;
    friend class DLinkedList;
};

class DLinkedList {
   public:
    DLinkedList();
    ~DLinkedList();
    bool empty() const;
    const string& front() const;
    const string& back() const;
    void addFront(const string& e);
    void addBack(const string& e);
    void removeFront();
    void removeBack();

   private:
    DNode* header;
    DNode* trailer;

   protected:
    void add(DNode* v, const string& e);
    void remove(DNode* v);
};

DLinkedList::DLinkedList() {
    header = new DNode;
    trailer = new DNode;
    header->next = trailer;
    trailer->prev = header;
}

DLinkedList::~DLinkedList() {
    while (!empty()) removeFront();
    delete header;
    delete trailer;
}

bool DLinkedList::empty() const { return (header->next == trailer); }

const string& DLinkedList::front() const { return header->next->ele; }

const string& DLinkedList::back() const { return trailer->prev->ele; }

// insert new node before v
void DLinkedList::add(DNode* v, const string& e) {
    DNode* u = new DNode;
    u->ele = e;
    u->next = v;
    u->prev = v->prev;
    v->prev->next = v->prev = u;
}

void DLinkedList::addFront(const string& e) { add(header->next, e); }

void DLinkedList::addBack(const string& e) { add(trailer, e); }

void DLinkedList::remove(DNode* v) {
    DNode* u = v->prev;
    DNode* w = v->next;
    u->next = w;
    w->prev = u;
    delete v;
}

void DLinkedList::removeBack() { remove(trailer->prev); }

void DLinkedList::removeFront() { remove(header->next); }

int main() { return 0; }