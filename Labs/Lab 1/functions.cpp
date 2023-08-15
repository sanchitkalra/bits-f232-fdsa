#include <cstdlib>
#include <iostream>

using namespace std;
bool testSum(int arr[], int n);

int main() {
    int arr[6] = {4, 4, 7, 5, 5, 2};
    bool result = testSum(arr, 6);

    if (result)
        cout << "sum of all numbers is even" << endl;
    else
        cout << "sum of all numbers is odd" << endl;

    return EXIT_SUCCESS;
}

bool testSum(int arr[], int n) {
    int sum = 0;
    for (int k = 0; k < n; k++) sum += arr[k];

    return (sum % 2) == 0;
}