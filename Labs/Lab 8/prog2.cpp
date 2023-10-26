/* Bubble Sort in a Doubly Linked List */

#include <iostream>

using namespace std;

// basic structure of a doubly linked list node
class doubly_linked_list_node {
 private:
  int data;
  doubly_linked_list_node *nextPtr;
  doubly_linked_list_node *prevPtr;

 public:
  doubly_linked_list_node(int item) {
    // call to designated constructor
    doubly_linked_list_node(item, NULL, NULL);
  }
  // designated constructor
  doubly_linked_list_node(int item, doubly_linked_list_node *prev,
                          doubly_linked_list_node *next) {
    data = item;
    prevPtr = prev;
    nextPtr = next;
  }
  int getData();
  doubly_linked_list_node *getNext();
  doubly_linked_list_node *getPrev();
  void setNext(doubly_linked_list_node *newNext);
  void setPrev(doubly_linked_list_node *newPrev);
};

typedef doubly_linked_list_node node;

int node::getData() { return data; }

node *node::getNext() { return nextPtr; }

node *node::getPrev() { return prevPtr; }

void node::setNext(node *newNext) { nextPtr = newNext; }

void node::setPrev(node *newPrev) { prevPtr = newPrev; }

// basic functionalities in a doubly linked list data structure.
class doubly_linked_list {
 private:
  node *head, *tail;
  void bubbleSort();
  void swap(node *, node *);

 public:
  doubly_linked_list() { head = tail = NULL; }
  void append(int item);
  bool isEmpty();
  void sort();
  void display();
};

typedef doubly_linked_list list;

// appends the given item at the end of the list
void list::append(int item) {
  if (isEmpty()) {
    head = tail = new node(item, NULL, NULL);
  } else {
    tail->setNext(new node(item, tail, NULL));
    tail = tail->getNext();
  }
}

// utility method to check if the list is empty
bool list::isEmpty() { return head == NULL; }

// sorts the given list
void list::sort() {
  if (isEmpty()) {
    return;
  }
  bubbleSort();
}

// Implementing bubble sort algorithm in a Doubly Linked List
// Time Complexity:
// Best Case = Omega(n)
// Worst Case = Big-Oh(n^2)
void list::bubbleSort() {
  node *start = head, *end = tail;
  int swapCount = 0;
  while (start != end) {
    while (true) {
      // if [start]'s next node is [end] node
      if (start->getNext() == end) {
        if (start->getData() > end->getData()) {
          // swap the nodes
          swap(start, end);
          // increment the swap count variable
          swapCount++;
        } else {
          // end move leftwards
          // shrink the size of unsorted list
          end = start;
        }
        break;
      }
      // if [start]'s next node has smaller data
      if (start->getData() > start->getNext()->getData()) {
        // first, update start pointer
        start = start->getNext();
        // now swap the nodes
        swap(start->getPrev(), start);
        // increment the swap count variable
        // missing code B (one line);
        swapCount++;
      }
      // move forward
      // missing code C (one line)
      start = start->getNext();
    }

    // we again start from the [head] node
    start = head;
    // reset swapCount variable.
    swapCount = 0;
  }
}

// utility method to swap the two adjacent nodes of the list
void list::swap(node *a, node *b) {
  if (a->getPrev() == b) {
    swap(a, b);
  }
  // fix the head pointer
  if (head == a || head == b) {
    if (head == a) {
      head = b;
    } else {
      head = a;
    }
  }
  // fix the tail pointer
  if (tail == a || tail == b) {
    // Missing code D (multiple lines)
    if (tail == a)
      tail = b;
    else
      tail = a;
  }
  // update [a]'s next pointer
  a->setNext(b->getNext());
  // update [b]'s next pointer

  // missing code E (one line)
  b->setNext(a);

  // update the prev pointer of [a]'s new next node
  if (a->getNext() != NULL) {
    a->getNext()->setPrev(a);
  }
  // update [b]'s prev pointer
  b->setPrev(a->getPrev());
  // update [a]'s prev pointer
  a->setPrev(b);
  // update the next pointer of [b]'s new prev node
  if (b->getPrev() != NULL) {
    b->getPrev()->setNext(b);
  }
}

// utility method to display the list contents
void list::display() {
  if (isEmpty()) {
    cout << "Empty List!\n";
    return;
  }
  node *ptr;
  cout << "NULL";
  for (ptr = head; ptr != tail; ptr = ptr->getNext()) {
    cout << " <- " << ptr->getData() << " -> ";
  }
  cout << " <- " << tail->getData() << " -> "
       << "NULL" << endl;
}

int main() {
  list li;
  li.append(20);
  li.append(30);
  li.append(15);
  cout << "Before Sorting:\n";
  li.display();
  li.sort();
  cout << "After Sorting:\n";
  li.display();
  li.sort();
  li.append(10);
  li.append(25);
  li.append(35);
  cout << "Before Sorting:\n";
  li.display();
  li.sort();
  cout << "After Sorting:\n";
  li.display();
  return 0;
}