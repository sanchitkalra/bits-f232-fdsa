#include <bits/stdc++.h>
using namespace std;

class Course {
   private:
    vector<int> courseMarks;

   public:
    string name;
    string IC;
    int numberOfStudents;
    int maxMarks;
    Course(string name, string IC, int numberOfStudents, int maxMarks)
        : name(name),
          IC(IC),
          numberOfStudents(numberOfStudents),
          maxMarks(maxMarks) {}
    vector<int> getMarks() { return courseMarks; }
    void setCourseMarks(vector<int>& v) {}
    bool evaluateAnswer(int givenAnswer, int expectedAnswer) {
        return (givenAnswer == expectedAnswer);
    }
    bool evaluateAnswer(string givenAnswer, string expectedAnswer) {
        return (givenAnswer == expectedAnswer);
    }
    bool evaluateAnswer(float givenAnswer, float expectedAnswer) {
        return (givenAnswer == expectedAnswer);
    }
};
class Lab : public Course {
   private:
    vector<int> labMarks = vector<int>(numberOfStudents);

   public:
    void setLabMarks(vector<int>& v) {}
    int countNC(int minMarks) {
        int count = 0;
        vector<int> courseMarks = getMarks();
        for (int k = 0; k < numberOfStudents; k++) {
            if (labMarks[k] + courseMarks[k] < minMarks) count++;
        }
        return count;
    }
};

int main() { return 0; }