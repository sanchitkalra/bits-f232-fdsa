#include <iostream>
using namespace std;

class Circle {
   private:
    double radius;

   public:
    void compute_area(double r) {
        radius = r;
        double area = 3.14 * radius * radius;

        cout << "Radius: " << radius << endl;
        cout << "Area: " << area << endl;
    }
};

int main() {
    Circle circle;
    circle.compute_area(7.2);

    return EXIT_SUCCESS;
}