#include <bits/stdc++.h>
using namespace std;

class FamilyNode {
   public:
    vector<FamilyNode *> children;
    string name;
    int age;
    float income;
    string occupation;
    // declare other members as per question's requirement
};

// Note:Input of nodes will be taken in order according to pre-order traversal
// of tree.
FamilyNode *buildTree() {
    string name;
    cout << "Enter name of member" << endl;
    cin >> name;
    int age;
    cout << "Enter age of member" << endl;
    cin >> age;
    float income;
    cout << "Enter income of member" << endl;
    cin >> income;
    string occupation;
    cout << "Enter occupation of member" << endl;
    cin >> occupation;

    int numOfChildren;
    cout << "Enter number of children" << endl;
    cin >> numOfChildren;

    FamilyNode *node = new FamilyNode();
    // Initialize the node
    node->name = name;
    node->age = age;
    node->income = income;
    node->occupation = occupation;

    for (int i = 0; i < numOfChildren; i++) {
        // Build tree rooted at child i. Add this to children vector of current
        // node.
    }

    return node;
}

// This function checks if a node with given parameters exists or not
bool checkIfNodeExists(FamilyNode *node, string name, int age, float income,
                       string occupation) {
    // Complete the code
    bool res = false;

    if (node->name == name && node->age == age && node->income == income &&
        node->occupation == occupation) {
        res = true;
    } else {
        for (auto it = node->children.begin(); it != node->children.end();
             it++) {
            res =
                res || checkIfNodeExists((*it), name, age, income, occupation);
        }
    }

    return res;
}

void removeNode(FamilyNode *node, FamilyNode *parent, string name, int age,
                float income, string occupation) {
    if (node->name.compare(name) == 0 && node->age == age &&
        node->income == income &&
        node->occupation == occupation)  // Complete the condition to check if
                                         // current node is required node
    {
        // Complete the code to remove current node from tree
        // Replace current node with children having highest income
        // Update the children vector of current node and parent accordingly

        // finding the child with the highest income
        FamilyNode *v = NULL;
        for (auto it = node->children.begin(); it != node->children.end();
             it++) {
            if (v == NULL || (*it)->income > v->income) {
                v = (*it);
            }
        }

        if (v == NULL) {
            // the node has no children, move on
            return;
        }

        // working with the siblings of the highest income child
        // creating a new vector for the new parent node
        vector<FamilyNode *> vec;

        // siblings in order before the child with max income
        int i = 0;
        FamilyNode *v1 = node->children[i];
        while (v1 != v) {
            vec.push_back(v1);
            i++;
        }

        // adding the max income child's children
        for (auto it = node->children.begin(); it != node->children.end();
             it++) {
            vec.push_back((*it));
        }

        // adding the leftover siblings
        i++;
        while (i < node->children.size()) {
            vec.push_back(v1);
            i++;
        }

        // making the new vector the children of the max income child
        v->children = vec;
        node = v;
    }

    // Continue the process for other nodes
}

// Complete the recursive function to calculate total income of a family
float getTotalIncome(FamilyNode *node) {
    float totalIncome = node->income;  // Complete initialization of totalIncome

    for (int i = 0; i < node->children.size(); i++) {
        // Complete the code
        totalIncome += getTotalIncome(node->children[i]);
    }

    return totalIncome;
}

// Complete the recursive function to calculate total income of a family
int getTotalAge(FamilyNode *node) {
    int totalAge = node->age;  // Complete initialization of totalIncome

    for (int i = 0; i < node->children.size(); i++) {
        // Complete the code
        totalAge += getTotalAge(node->children[i]);
    }

    return totalAge;
}

// The function returns the ancestor of family having highest income-to-age
// ratio
FamilyNode *getHighestIncomeAgeRatioFamily(vector<FamilyNode *> &familyTrees) {
    // Complete the code
    FamilyNode *v = NULL;
    float bestRatio = 0;

    for (int i = 0; i < familyTrees.size(); i++) {
        float currFamilyTotalIncome = getTotalIncome(familyTrees[i]);
        int currFamilyTotalAge = getTotalAge(familyTrees[i]);
        float currFamilyRatio = currFamilyTotalIncome / currFamilyTotalAge;
        // Complete the code here
        if (v == NULL || currFamilyRatio > bestRatio) {
            v = familyTrees[i];
        }
    }

    // Return the ancestor node of family with highest income-to-age ratio
    return v;
}

bool comp(FamilyNode *v1, FamilyNode *v2) {
    return getTotalIncome(v1) > getTotalIncome(v2);
}

void printFamiliesInDecrOrder(vector<FamilyNode *> &familyTrees) {
    // Complete the code
    vector<FamilyNode *> vec(familyTrees);
    sort(vec.begin(), vec.end(), comp);
    for (auto x : vec) {
        cout << x->name << " ";
    }
    cout << endl;
}

int main() {
    int numOfFamilies;
    cout << "Enter the number of families\n";
    cin >> numOfFamilies;

    vector<FamilyNode *>
        familyTrees;  // This vector stores ancestor nodes of all families

    for (int i = 0; i < numOfFamilies; i++) {
        familyTrees.push_back(buildTree());
    }

    while (1) {
        int choice;
        cout << "1. Remove node" << endl;
        cout << "2. Find Highest Income-To-Age-Ratio Family" << endl;
        cout << "3. Print Family(Ancestor) Names in Decreasing Income Order"
             << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice" << endl;

        cin >> choice;

        switch (choice) {
            case 1: {
                int num;
                cout << "Enter Family number whose node is to be removed"
                     << endl;
                cin >> num;
                cout << "Enter name, age, income and occupation of member to "
                        "be removed"
                     << endl;
                string name, occupation;
                int age;
                float income;
                cin >> name >> age >> income >> occupation;

                if (!checkIfNodeExists(familyTrees[num], name, age, income,
                                       occupation))
                    cout << "No such family member exists" << endl;
                else
                    removeNode(familyTrees[num], NULL, name, age, income,
                               occupation);
                break;
            }
            case 2: {
                FamilyNode *node = getHighestIncomeAgeRatioFamily(familyTrees);
                cout << "Name of ancestor of family with highest total income "
                        "is "
                     << node->name;
                break;
            }
            case 3: {
                printFamiliesInDecrOrder(familyTrees);
                break;
            }
            case 4: {
                return 0;
                break;
            }
            default: {
                cout << "Incorrect choice!!!" << endl;
                break;
            }
        }
    }

    return 0;
}