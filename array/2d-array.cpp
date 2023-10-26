#include <bits/stdc++.h>
using namespace std;

int main() {
    // a 2d array, each element of the base array is a collection of pointers
    // which themselves represent actual arrays
    const int x = 3, y = 4;

    // declaring a 2d array of size x*y
    int** M = new int*[x];  // decalre an array of pointers. M is a double
                            // pointer because it refers to an array to
                            // pointers, and that reference itself is a pointer
    for (int k = 0; k < x; k++) {
        M[k] = new int[y];
    }

    // to delete the 2d-array, we go in the reverse of the creation steps.
    // first we delete the inner arrays, and then the main array itself
    for (int k = 0; k < x; k++) {
        delete[] M[k];
    }
    delete[] M;

    // we can also declare a 2d-array using vector of vector
    vector<vector<int>>(
        x, vector<int>(
               y));  // this way the second element of the vector constructor
                     // allows us to choose the initialisation value for each
                     // element in the vector. The single parameter vector
                     // constructor expects size and allocates sufficient memory
                     // internally. Now using that constructor again as the
                     // second parameter of the parent vector, we initialise
                     // each element of the vector with a vector of size y.

    return 0;
}