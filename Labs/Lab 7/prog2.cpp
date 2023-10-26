#include <iostream>
#include <queue>

using namespace std;

template <typename E>
class Stack {
 private:
  queue<E> q1;  // this is the main queue
  queue<E> q2;  // helper queue to support stack behaviour.
  void displayHelper(queue<E>);

 public:
  void push(E elem);
  void pop();
  E top();
  int size();
  bool empty();
  void display();
};

// inserts the given element into the Stack
template <typename E>
void Stack<E>::push(E elem) {
  q1.push(elem);
}

// removes the element from the TOP of the Stack
template <typename E>
void Stack<E>::pop() {
  if (q1.empty()) {
    throw("Stack Underflows!");
  }
  int q1_size = q1.size();
  for (int i = 0; i < q1_size - 1; i++) {
    q2.push(q1.front());
    q1.pop();
  }

  q1.pop();

  // Missing Code A

  int q2_size = q2.size();
  for (int i = 0; i < q2_size; i++) {
    q1.push(q2.front());
    q2.pop();
  }
}

// returns the element at the TOP of the Stack
template <typename E>
E Stack<E>::top() {
  if (q1.empty()) {
    throw("Stack is Empty!");
  }
  int q1_size = q1.size();
  for (int i = 0; i < q1_size - 1; i++) {
    q2.push(q1.front());
    q1.pop();
  }

  //   cout << "q1 " << q1.size() << " -> ";
  //   displayHelper(q1);

  E topElem = q1.front();
  q2.push(topElem);
  q1.pop();

  // Missing code B
  int q2_size = q2.size();
  for (int i = 0; i < q2_size; i++) {
    q1.push(q2.front());
    q2.pop();
  }

  //   cout << "q1 " << q1.size() << " -> ";
  //   displayHelper(q1);

  return topElem;
}

// returns the number of elements in the Stack
template <typename E>
int Stack<E>::size() {
  return q1.size();
}

// returns true if stack is empty, false otherwise
template <typename E>
bool Stack<E>::empty() {
  return q1.empty();
}

// shows the contents of the Stack
template <typename E>
void Stack<E>::display() {
  if (q1.empty()) {
    cout << "Stack is Empty!" << endl;
    return;
  }
  cout << "TOP -> ";
  displayHelper(q1);
}

template <typename E>
void Stack<E>::displayHelper(queue<E> queue) {
  if (queue.empty()) return;
  E frontElem = queue.front();
  queue.pop();
  displayHelper(queue);
  cout << '\t' << frontElem << endl;
  queue.push(frontElem);
}

int main() {
  Stack<float> stack;

  stack.display();  // Stack is Empty!

  stack.push(15.5);
  cout << "15.5 pushed into the Stack." << endl;
  stack.push(23);
  cout << "23 pushed into the Stack." << endl;
  stack.push(20.5);
  cout << "20.5 pushed into the Stack." << endl;

  stack.display();

  cout << "Size of the Stack = " << stack.size() << endl;

  cout << "Elem at the TOP: " << stack.top() << endl;

  cout << "Popping..." << endl;
  stack.pop();

  cout << "Elem at the TOP: " << stack.top() << endl;

  stack.display();

  stack.push(35);
  cout << "35 pushed into the Stack." << endl;

  stack.display();

  return 0;
}