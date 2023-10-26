#include <iostream>
using namespace std;

class DLinkedList;

typedef string Elem;  // list element type
class DNode {         // doubly linked list node
 private:
  Elem elem;                 // node element value
  DNode* prev;               // previous node in list
  DNode* next;               // next node in list
  friend class DLinkedList;  // allow DLinkedList access
};

class DLinkedList {  // doubly linked list
 public:
  DLinkedList();                 // constructor
  ~DLinkedList();                // destructor
  bool empty() const;            // is list empty?
  const Elem& front() const;     // get front element
  const Elem& back() const;      // get back element
  void addFront(const Elem& e);  // add to front of list
  void addBack(const Elem& e);   // add to back of list
  void removeFront();            // remove from front
  void removeBack();             // remove from back
  void listReverse();            // reverse the list
  void traverse();               // traverse the list
 private:                        // local type definitions
  DNode* header;                 // list sentinels
  DNode* trailer;

 protected:                           // local utilities
  void add(DNode* v, const Elem& e);  // insert new node before v
  void remove(DNode* v);              // remove node v
};

DLinkedList::DLinkedList() {  // constructor
  header = new DNode;         // create sentinels
  trailer = new DNode;
  header->next = trailer;  // have them point to each other
  trailer->prev = header;
}

DLinkedList::~DLinkedList() {      // destructor
  while (!empty()) removeFront();  // remove all but sentinels
  delete header;                   // remove the sentinels
  delete trailer;
}

bool DLinkedList::empty() const  // is list empty?
{
  return (header->next == trailer);
}

const Elem& DLinkedList::front() const  // get front element
{
  return header->next->elem;
}

const Elem& DLinkedList::back() const  // get back element
{
  return trailer->prev->elem;
}

void DLinkedList::add(DNode* v, const Elem& e) {  // insert new node before v
  DNode* u = new DNode;
  u->elem = e;        // create a new node for e
  u->next = v->next;  // link u in between v
  u->prev = v;
  v->next->prev = u;
  v->next = u;
}

void DLinkedList::addFront(const Elem& e)  // add to front of list
{
  add(header, e);
}

void DLinkedList::addBack(const Elem& e)  // add to back of list
{
  add(trailer->prev, e);
}

void DLinkedList::remove(DNode* v) {  // remove node v
  DNode* u = v->prev;                 // predecessor
  DNode* w = v->next;                 // successor
  u->next = w;                        // unlink v from list
  w->prev = u;
  delete v;
}

void DLinkedList::removeFront()  // remove from font
{
  remove(header->next);
}

void DLinkedList::removeBack()  // remove from back
{
  remove(trailer->prev);
}

void DLinkedList::listReverse() {  // reverse a list
  DLinkedList T;                   // temporary list
  while (!this->empty()) {         // reverse L into T
    string s = this->front();
    this->removeFront();
    T.addFront(s);
  }
  while (!T.empty()) {  // copy T back to L
    string s = T.front();
    T.removeFront();
    this->addBack(s);
  }
}

void DLinkedList::traverse() {
  DNode* temp = header;
  while (temp != trailer) {
    cout << temp->elem << " ";
    temp = temp->next;
  }
  cout << endl;
}

typedef string Elem;  // deque element type
class LinkedDeque {   // deque as doubly linked list
 public:
  LinkedDeque();                    // constructor
  int size() const;                 // number of items in the deque
  bool empty() const;               // is the deque empty?
  const Elem& front();              // the first element
  const Elem& back();               // the last element
  void insertFront(const Elem& e);  // insert new first element
  void insertBack(const Elem& e);   // insert new last element
  void removeFront();               // remove first element
  void removeBack();                // remove last element
 private:                           // member data
  DLinkedList D;                    // linked list of elements
  int n;                            // number of elements
};

LinkedDeque::LinkedDeque()  // constructor
    : D(), n(0) {}

void LinkedDeque::insertFront(const Elem& e) {
  D.addFront(e);
  n++;
}

void LinkedDeque::insertBack(const Elem& e) {  // insert new last element
  D.addBack(e);
  n++;
}

void LinkedDeque::removeFront() {  // remove first element
  if (empty())
    cout << "removeFront of empty deque\n";
  else {
    D.removeFront();
    n--;
  }
}

void LinkedDeque::removeBack() {  // remove last element
  if (empty())
    cout << "removeBack of empty deque\n";
  else {
    D.removeBack();
    n--;
  }
}

int LinkedDeque::size() const  // number of items in the queue
{
  return n;
}

bool LinkedDeque::empty() const  // is the queue empty?
{
  return n == 0;
}

const Elem& LinkedDeque::front() {  // get the front element
  if (empty()) cout << "front of empty queue\n";
  return D.front();  // list front is queue front
}

const Elem& LinkedDeque::back() {  // get the front element
  if (empty()) cout << "back of empty queue\n";
  return D.back();  // list front is queue front
}

typedef string Elem;  // element type
class DequeStack {    // stack as a deque
 public:
  DequeStack();              // constructor
  int size() const;          // number of elements
  bool empty() const;        // is the stack empty?
  const Elem& top();         // the top element
  void push(const Elem& e);  // push element onto stack
  void pop();                // pop the stack
 private:
  LinkedDeque D;  // deque of elements
};

DequeStack::DequeStack()  // constructor
    : D() {}
// number of elements
int DequeStack::size() const { return D.size(); }
// is the stack empty?
bool DequeStack::empty() const { return D.empty(); }
// the top element
const Elem& DequeStack::top() {
  if (empty()) cout << "top of empty stack\n";
  return D.front();
}
// push element onto stack
void DequeStack::push(const Elem& e) { D.insertFront(e); }
// pop the stack
void DequeStack::pop() {
  if (empty()) cout << "pop of empty stack\n";
  D.removeFront();
}

void printOptions() {
  cout << "1 : Push\n";
  cout << "2 : Pop\n";
  cout << "3 : Get top\n";
  cout << "4 : Get size\n";
  cout << "5 : Check if stack is empty\n";
  cout << "6 : Exit\n";
}

int main() {
  DequeStack ds = DequeStack();
  int opt = -1;
  while (opt != 6) {
    cin >> opt;
    switch (opt) {
      case 1: {
        string aux;
        cin >> aux;
        cout << "Pushing " << aux << endl;
        ds.push(aux);
        break;
      }
      case 2: {
        cout << "Popping\n";
        ds.pop();
        break;
      }
      case 3: {
        cout << "Top element\n";
        cout << ds.top() << endl;
        break;
      }
      case 4: {
        cout << "Getting size\n";
        cout << ds.size() << endl;
        break;
      }
      case 5: {
        cout << "Stack is " << (ds.empty() ? "" : "not") << "empty\n";
        break;
      }
      case 6: {
        break;
      }
    }
  }
  return 0;
}