#include <iostream>

using namespace std;

class Dynamic1DArray {
 public:
  Dynamic1DArray(const int capacity);
  ~Dynamic1DArray();
  void insertItem(const int item);
  void insertItemAtIndex(const int index, const int item);
  bool deleteItem(const int item);
  int deleteItemFromIndex(const int index);
  int linearSearch(const int item);
  int binarySearch(const int item);
  int getSize();
  bool isEmpty();
  bool isFull();
  void sort();
  void display();

 private:
  int *arr;
  int capacity;
  int size;
  void swap(int i, int j);
  void grow();
  void shrink();
};

Dynamic1DArray ::Dynamic1DArray(const int initialCapacity) {
  capacity = initialCapacity;
  size = 0;
  arr = new int[capacity]{0};
}

Dynamic1DArray ::~Dynamic1DArray() { delete arr; }

// inserts the given item into the array
// basically appends the given item at the end of the array
void Dynamic1DArray ::insertItem(const int item) {
  if (isFull()) grow();

  // increment current size of the array
  ++size;

  // now insert at the last index in the array
  arr[size - 1] = item;
}

// inserts the given item at the specific index
void Dynamic1DArray ::insertItemAtIndex(const int index, const int item) {
  if (index < 0 || index >= size) throw "Invalid Argument: index";
  if (isFull()) grow();

  // increment current size of the array
  ++size;

  // first shift the items towards right
  for (int i = size - 1; i > index; i--) arr[i] = arr[i - 1];

  // now insert item at this index
  arr[index] = item;
}

void Dynamic1DArray ::grow() {
  // double the capacity
  capacity <<= 1;

  // initialze the bigger array
  int *newArr = new int[capacity];

  // copy all the items to the new array
  for (int i = 0; i < size; i++) newArr[i] = arr[i];

  // update the global array pointer
  arr = newArr;
}

// deletes the given item from thw array
bool Dynamic1DArray ::deleteItem(const int item) {
  // first search for this item
  // for sorted array, we can use binarySearch()
  int index = linearSearch(item);

  if (index == -1) return false;  // deletion failure

  deleteItemFromIndex(index);

  return true;  // deletion success
}

// deletes the item from the given index
// returns the deleted item
int Dynamic1DArray ::deleteItemFromIndex(const int index) {
  if (isEmpty()) throw "Deletion from Empty Array";
  if (index < 0 || index >= size) throw "Invalid Argument: index";

  int item = arr[index];  // read the item at that index

  // left shift item hanging towards right
  for (int i = index; i < size - 1; i++) arr[i] = arr[i + 1];

  // decrement the size of the array
  --size;

  // if the size of the array becomes half of the max_capacity
  // then, shrink the given array
  if (size < (capacity >> 1)) shrink();

  return item;
}

void Dynamic1DArray ::shrink() {
  // capacity now reduces to half
  capacity >>= 1;

  // initialize the smaller array
  int *newArr = new int[capacity];

  // copy all items to the new array
  for (int i = 0; i < size; i++) newArr[i] = arr[i];

  // update the global array pointer
  arr = newArr;
}

// search for a given item in an unsorted array
// return the index location of the item
// or -1 if item does not exist in the array
// Time Complexity: O(n)
int Dynamic1DArray ::linearSearch(const int item) {
  for (int i = 0; i < size; i++) {
    if (arr[i] == item) return i;  // found
  }
  return -1;  // not found
}

// search for a given item in a sorted array
// return the index location of the item
// or -1 if item does not exist in the array
// Time Complexity: O(log n)
int Dynamic1DArray ::binarySearch(const int item) {
  int low = 0, high = size - 1;
  while (low <= high) {
    int mid = low + ((high - low) >> 1);
    if (item == arr[mid]) return mid;
    if (item < arr[mid])
      high = mid - 1;
    else
      low = mid + 1;
  }
  return -1;
}

// implementing insertion sort algorithm
// refer textbook for further explanation.
void Dynamic1DArray ::sort() {
  for (int j = 1; j < size; j++) {
    int key = arr[j];
    int i = j - 1;
    while (i > -1 && arr[i] > key) {
      arr[i + 1] = arr[i];
      i = i - 1;
    }
    arr[i + 1] = key;
  }
}

// returns true if array is empty, false otherwise
bool Dynamic1DArray ::isEmpty() { return size == 0; }

// returns true if array is full, false otherwise
bool Dynamic1DArray ::isFull() { return size == capacity; }

int Dynamic1DArray ::getSize() { return size; }

// utility method to display the given array
void Dynamic1DArray ::display() {
  if (isEmpty()) return;
  for (int i = 0; i < size - 1; i++) cout << arr[i] << " ";
  cout << arr[size - 1] << endl;
}

// utility method to swap items at given indices in the given array
void Dynamic1DArray ::swap(int i, int j) {
  int t = arr[i];
  arr[i] = arr[j];
  arr[j] = t;
}

int main() {
  // declare the initial capacity of the array
  int initialCapacity = 3;

  Dynamic1DArray arr(initialCapacity);

  arr.display();  // nothing

  arr.insertItem(5);
  arr.insertItem(3);
  arr.insertItem(11);

  arr.display();  // [5, 3, 11]

  arr.insertItemAtIndex(1, 7);

  arr.display();  // [5, 7, 3, 11]

  arr.sort();

  arr.display();  // [3, 5, 7, 11]

  arr.insertItem(15);
  arr.insertItem(16);  // no error! this is dynamic array

  arr.display();  // [3, 5, 7, 11, 15, 16]

  cout << arr.getSize() << endl;

  arr.deleteItem(11);

  arr.display();  // [3, 5, 7, 15]

  arr.deleteItem(16);

  arr.display();  // [3, 5, 7, 15]

  arr.deleteItemFromIndex(0);

  arr.display();  // [5, 7, 15]

  arr.deleteItemFromIndex(1);

  arr.display();  // [5, 15]

  cout << arr.getSize() << endl;

  return 0;
}