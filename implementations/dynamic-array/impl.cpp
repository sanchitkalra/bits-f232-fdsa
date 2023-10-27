#include <bits/stdc++.h>
using namespace std;

template <typename T>
class DynamicArray {
   private:
    T *arr;    // the pointer to the actual array memory
    int cap;   // the max number of elements storable
    int size;  // actual number of elements stored in the array

    void grow() {  // used when capacity is over
        cap *= 2;  // double the capacity
        T *a2 = new T[cap];
        for (int k = 0; k < size; k++) {
            a2[k] = arr[k];
        }
        delete arr;  // delete array's prev memory before referencing new memory
                     // using the same pointer to avoid a potential memory leak
        arr = a2;
    }

    void shrink() {  // size is less than half of the capacity
        cap /= 2;    // reduce capacity by half
        T *a2 = new T[cap];
        for (int k = 0; k < size; k++) {
            a2[k] = arr[k];
        }
        delete arr;  // delete array's prev memory before referencing new memory
                     // using the same pointer to avoid a potential memory leak
        arr = a2;
    }

   public:
    DynamicArray(const int capacity) {
        cap = capacity;
        size = 0;
        arr = new T[capacity];  // initialise an array of size capacity
    }
    ~DynamicArray() { delete arr; }

    void push_back(T element) {
        if (isFull()) {
            grow();
        }
        arr[size] = element;
        size++;
    }

    void pop_back() {
        size--;
        if (2 * size < cap) {
            shrink();
        }
    }

    int size() { return size; }
    bool isFull() { return size == cap; }
    bool isEmpty() { return size == 0; }

    void insertAtIndex(const int index, const T element) {
        if (index < 0 || index >= size) throw "Invalid index";
        if (isFull()) grow();

        size++;
        for (int k = size - 1; k > index; k--) arr[k] = arr[k - 1];
        arr[index] = element;
    }
};