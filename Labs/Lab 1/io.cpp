#include <cstdlib>
#include <iostream>

int main() {
    int x, y;
    std::cout << "Please enter two numbers: " << std::endl;

    std::cin >> x >> y;

    int sum = x + y;
    std::cout << "sum = " << sum << std::endl;

    return EXIT_SUCCESS;
}