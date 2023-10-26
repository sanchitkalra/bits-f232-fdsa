#include <bits/stdc++.h>
using namespace std;

class Queue {
   public:
    int front, rear, size;
    unsigned int cap;
    int* arr;
};

class Queue2 {
   private:
    int front, rear, size;
    unsigned int cap;
    int* arr;

   public:
    Queue2() {
        cap = 100;
        front = size = 0;
        rear = cap - 1;
        arr = new int[(cap * sizeof(int))];
    }
};

void createSecondQueue() { Queue2 q = Queue2(); }

Queue* createQueue(unsigned int cap) {
    Queue* queue = new Queue();
    queue->cap = cap;

    queue->front = queue->size = 0;
    queue->rear = queue->cap - 1;

    queue->arr = new int[(queue->cap * sizeof(int))];

    return queue;
}

int main() { return 0; }