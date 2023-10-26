#include <bits/stdc++.h>

#include "timer.h"
using namespace std;

// This function returns the total number of ways to reach stair n from stair i
int totalWays(int i, int n) {
  // Base Case
  if (i == n) return 1;
  if (i > n) return 0;

  // You can take 1 step, 2 steps or 3 steps

  // Find number of ways if you take 1 step
  // Fill the argument marked as ?
  // Think what will be stair number if you take one step from stair i
  int takeOneStep = totalWays(i + 1, n);

  // Find number of ways if you take 2 steps
  // Fill the argument marked as ?
  int takeTwoSteps = totalWays(i + 2, n);

  // Find number of ways if you take 3 steps
  // Fill the argument marked as ?
  int takeThreeSteps = totalWays(i + 3, n);

  // Write a return statement to return the total number of ways.
  return takeOneStep + takeTwoSteps + takeThreeSteps;
}

int main() {
  int n;
  cout << "Enter the number of stairs in staircase n" << endl;
  cin >> n;

  Timer t;

  t.start();
  int out = totalWays(0, n);
  t.stop();

  cout << "The total number of ways to reach top of staircase is " << out
       << "; computed in " << t.getDurationInMicroSeconds() << endl;
}