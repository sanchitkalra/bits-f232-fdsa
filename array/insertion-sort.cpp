#include <bits/stdc++.h>
using namespace std;

void print(int arr[], int n) {
    for (int k = 0; k < n; k++) cout << arr[k] << " ";
    cout << endl;
}

void sort(int arr[], int n) {
    for (int k = 0; k < n; k++) {
        int cur = arr[k];
        int j = k - 1;
        while (j >= 0 && arr[j] > cur) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = cur;
        cout << "Step " << k << ":";
        print(arr, 9);
    }
}

int main() {
    int arr[] = {3, 6, 1, 2, 7, 0, 3, 4, 4};
    print(arr, 9);

    sort(arr, 9);
    print(arr, 9);

    return 0;
}