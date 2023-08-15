// Task 4
#include <iostream>
using namespace std;

class Emp {
   private:
    int salary;
    int workHours;  // number of hours of work per dat

   public:
    void setInfo(int salary, int workHours) {
        this->salary = salary;
        this->workHours = workHours;
    };

    void addSalary() {
        if (this->salary < 30000) this->salary += 2000;
    }

    void addWork() {
        if (this->workHours > 8) this->salary += 100;
    }

    void getInfo() { cout << "Salary: " << this->salary << endl; }
};

int main() {
    Emp emp;
    emp.setInfo(25000, 9);
    emp.addSalary();
    emp.addWork();
    emp.getInfo();

    return 0;
}