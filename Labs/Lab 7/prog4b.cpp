#include <deque>
#include <iostream>

using namespace std;

template <typename E>
class Queue {
 private:
  deque<E> dq;

 public:
  void enqueue(E elem);
  void dequeue();
  E front();
  int size();
  bool empty();
  void display();
};

template <typename E>
void Queue<E>::enqueue(E elem) {
  // insert the element at the rear end of the Deque
  // Missing code A
  dq.push_back(elem);
}

template <typename E>
void Queue<E>::dequeue() {
  // missing code B
  dq.pop_front();
}

template <typename E>
E Queue<E>::front() {
  if (dq.empty()) throw("Queue is Empty!");
  // Missing code C
  return dq.front();
}

template <typename E>
int Queue<E>::size() {
  return dq.size();
}

template <typename E>
bool Queue<E>::empty() {
  return dq.empty();
}

template <typename E>
void Queue<E>::display() {
  if (dq.empty()) {
    cout << "Queue is Empty!" << endl;
    return;
  }
  cout << "FRONT -> ";
  int dq_size = dq.size();
  for (int i = 0; i < dq_size; i++) {
    // display the item at the front end of the Deque
    E frontElem = dq.front();
    cout << frontElem << " ";
    // dequeue from the front end of the Deque
    dq.pop_front();
    // enqueue this item at the rear end of the Deque
    dq.push_back(frontElem);
  }
  cout << endl;
}

int main() {
  Queue<string> queue;

  queue.display();  // Stack is Empty!

  queue.enqueue("Pilani");
  cout << "Pilani enqueued into the Queue." << endl;
  queue.enqueue("Goa");
  cout << "Goa enqueued into the Queue." << endl;
  queue.enqueue("Hyd");
  cout << "Hyd enqueued into the Queue." << endl;

  queue.display();

  cout << "Size of the Queue = " << queue.size() << "." << endl;

  cout << "Elem at the FRONT: " << queue.front() << endl;

  cout << "Dequeuing..." << endl;
  queue.dequeue();

  cout << "Elem at the FRONT: " << queue.front() << endl;

  queue.display();

  queue.enqueue("Dubai");
  cout << "Dubai enqueued into the Queue." << endl;

  queue.display();

  return 0;
}