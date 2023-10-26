#include <iostream>
#include <queue>

using namespace std;

// idle queue stores the jobs sitting idle.
queue<int> idleQueue;

// ready queue stores the jobs in the ready queue at a given time instant.
queue<int> readyQueue;

// the range of sorted list of idle jobs [1 to N]
int N;

// the rate at which the Jobs enter into the Ready Queue
int P;

// the rate at which the Jobs leave the Ready Queue for CPU execution
int Q;

// the time instant at which the Ready Queue will be displayed
int T;

void initIdleQueue() {
  for (int i = 1; i <= N; i++) idleQueue.push(i);
}

// The Heart of the job scheduling mechanism
// picks up jobs from the idle queue and puts them into ready queue at the rate
// 'P' picks up jobs from the ready queue at the rate 'Q'
void jobScheduler() {
  // picking up jobs from idle queue and pushing into readyQueue
  //   displayReadyQueue();
  for (int i = 1; i <= P; i++) {
    // Missing Code A
    if (idleQueue.empty()) break;
    readyQueue.push(idleQueue.front());
    idleQueue.pop();
  }
  // picking up jobs from ready queue at the rate Q
  // Missing Code B
  for (int i = 1; i <= Q; i++) {
    if (readyQueue.empty()) break;
    int frontElem = readyQueue.front();
    // Missing Code C
    readyQueue.pop();
  }
}

void displayReadyQueue() {
  queue<int> tempQueue;
  int frontElem;
  cout << "[";
  if (!readyQueue.empty()) {
    int rq_size = readyQueue.size();
    for (int i = 1; i < rq_size; i++) {
      frontElem = readyQueue.front();
      cout << frontElem << ", ";
      tempQueue.push(frontElem);
      readyQueue.pop();
    }
    frontElem = readyQueue.front();
    cout << frontElem;
    tempQueue.push(frontElem);
    readyQueue.pop();
  }
  while (!tempQueue.empty()) {
    readyQueue.push(tempQueue.front());
    tempQueue.pop();
  }
  cout << "]" << endl;
}

int main() {
  cout << "Enter N (> 0): ";
  cin >> N;
  cout << "Enter P (> 0): ";
  cin >> P;
  cout << "Enter Q (> 0): ";
  cin >> Q;
  cout << "Enter T (> 0): ";
  cin >> T;

  // initialize idle queue
  initIdleQueue();

  for (int t = 1; t <= T; t++) {
    // run the job scheduler for this time instant.
    jobScheduler();
  }

  displayReadyQueue();

  return 0;
}