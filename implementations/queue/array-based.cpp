#include <bits/stdc++.h>
using namespace std;

class Queue {
   private:
    int front, rear, size;
    unsigned int cap;
    int* arr;

   public:
    Queue() {
        cap = 100;
        front = size = 0;
        rear = cap - 1;
        arr = new int[(cap * sizeof(int))];
    }
};

int main() { return 0; }