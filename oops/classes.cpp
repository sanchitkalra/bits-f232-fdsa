#include <bits/stdc++.h>
using namespace std;

class Person {
   private:
    int idNum;

   protected:
    string name;

   public:
    Person() {}  // default constructor
    Person(const string& nm, const int& id)
        : name(nm), idNum(id) {}                        // constructor
    ~Person() {}                                        // destructor
    void print() { cout << "Person's print" << endl; }  // parent's print
    virtual void virtualPrint() {
        cout << "Person's virtual print" << endl;
    }  // parent's virtual print. Because Person has at least one virtual
       // function, it is said to be a polymorphic class
    virtual void aFuncNotOverridden() {
        cout << "a func not overridden in parent" << endl;
    }
    // virtual void pureVirtualFunc() = 0;  // Defining a pure virtual function
    // using "=0" syntactical sugar. When a class has a pure virtual function it
    // cannot be init independently but only using subclasses which implement
    // this function. Hence we're commenting this out
};

// Student is derived from Person (or in other words, Student inherits from
// Person)
// 3 kinds of inheritance:
// 1. public: public and protected members of base -> public and protected resp
// in child
// 2. protected: public and protected members of base -> both protected in
// child
// 3. private: public and protected members of base -> both private in child

class Student : public Person {  // Student is derived from Person and is a
                                 // subtype of Person => wherever we can use the
                                 // parent, we can use the child

   private:
    string major;
    int gradYear;

   public:
    Student() {}  // default constructor
    Student(const string& nm, const int& id, const string& maj, const int& year)
        : Person(nm, id),  // call the Person's constructor
          major(maj),
          gradYear(year) {
    }  // While init Student using it's constructor, the members of the super
       // class Person should also be int
       // parent constructor is called before the dervied class' constructor
    ~Student() {}  // destructor; imp part is that destructors are called in
                   // reverse order of constructors, ie, destructor of derived
                   // will be called before destructor of parent
                   // destructor of child cannot call destructor of parent
    void print() { cout << "Child's print" << endl; }  // child's print
    void funcExclusiveToStudent() {}  // func in Student but absent in Person
    virtual void virtualFuncExclusiveToStudent() {
    }  // func in Student but absent in Person but now virtual
    virtual void virtualPrint() {
        cout << "Child's virtual print" << endl;
    }  // child's virtual print, here virtualPrint definition in Student
       // overrides the virtualPrint definition in Person
    // virtual void pureVirtualFunc() {} -> this pure virtual function must be
    // implemented here in the subclass, not following which the program shall
    // give compilation errors.
};

int main() {
    Student* s = new Student("Sanchit", 2298, "EEE", 2025);
    s->print();  // will call only child's print, and not parent
    delete s;    // this would call child and then parent destructor

    Person* pp[10];         // declaring an array of Person
    pp[0] = new Person();   // valid
    pp[1] = new Student();  // valid

    // effect of static binding
    // when deciding which function to call in such a scenario, C++ gives
    // precedence to the declared type (in this case it is Parent and not
    // Student), and hence even when pp[1] is init with Student's constructor,
    // the parent's print will still be called.
    // Another imp thing to note is that for this same reason, you can't call
    // function exclusive to Student from pp[1].
    pp[0]->print();  // calls parent's print
    pp[1]->print();  // also calls parent's print.
    // following function if called, would throw an error
    // pp[1]->funcExclusiveToStudent();

    // effect of dynamic binding
    // when using dynamic binding using the virtual keyword, the decision to
    // call which function is taken at runtime provided both functions
    // conflicting this way are defined to be virtual
    pp[0]->virtualPrint();  // calls parent's print
    pp[1]->virtualPrint();  // calls child's print
    // the following still doesn't work
    // pp[1]->funcExclusiveToStudent();
    // even the following does not work as this function is not present in the
    // parent
    // pp[1]->virtualFuncExclusiveToStudent();
    // but we can do some magic with dynamic casting
    // dynamic casting can only be applied to polymorphic classes
    // dynamic_cast also checks if the casting is valid, if not, it returns a
    // null pointer (free error checking, hoorayyy!!!!)

    Student* sp = dynamic_cast<Student*>(
        pp[1]);  // casts an object of type Person to a type student
    sp->funcExclusiveToStudent();         // now valid
    sp->virtualFuncExclusiveToStudent();  // now valid

    Student* sp2 = dynamic_cast<Student*>(pp[0]);  // this wouldn't work
    if (sp2 == nullptr) cout << "Cast did not work" << endl;

    // more dyamic binding hehe
    Person* p = new Student();
    p->print();  // uses the parent print, because it is a not virtual function
                 // using static binding
    p->virtualPrint();  // this calls the child's print because of dynamic
                        // binding

    // specialisation
    // subclasses can specialise the virtual functions of the parent classes as
    // per their need but need not do so
    pp[0]->aFuncNotOverridden();  // valid
    pp[1]->aFuncNotOverridden();  // valid

    return 0;
}