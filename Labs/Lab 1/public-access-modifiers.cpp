#include <iostream>
using namespace std;

class Circle {
   public:
    double radius;

    double compute_area() { return 3.14 * radius * radius; }
    double compute_circumference() { return 2 * 3.14 * radius; }
};

class Rectangle {
   public:
    double height, width;

    double compute_area() { return width * height; }
    double compute_circumference() { return 2 * (width + height); }
};

int main() {
    Circle obj;
    obj.radius = 7.2;

    cout << "Radius is: " << obj.radius << endl;
    cout << "Area is: " << obj.compute_area() << endl;

    // Subtask 1:
    // Add circumference calculation to Circle class
    cout << "Circumference is: " << obj.compute_circumference() << endl;

    // Subtask 2:
    // Add Rectangle class (with area and circumference) and give option to user
    // to choose between Circle and Rectangle

    cout << endl
         << "Select shape: " << endl
         << "1 - Rectangle" << endl
         << "2 - Circle" << endl
         << endl;

    int selection;
    cin >> selection;

    switch (selection) {
        case 1:
            Rectangle rect;
            cout << endl << "Enter width and height: ";
            double width, height;
            cin >> width >> height;
            rect.height = height;
            rect.width = width;
            cout << "Area: " << rect.compute_area() << endl;
            cout << "Circumference: " << rect.compute_circumference() << endl;
            break;

        case 2:
            Circle circle;
            cout << endl << "Enter radius: ";
            double radius;
            cin >> radius;
            circle.radius = radius;
            cout << "Area: " << circle.compute_area() << endl;
            cout << "Circumference: " << circle.compute_circumference() << endl;
            break;

        default:
            cout << "Invalid selection" << endl;
            break;
    }

    return EXIT_SUCCESS;
}