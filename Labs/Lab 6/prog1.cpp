#include <iostream>
#include <unordered_map>
using namespace std;

unordered_map<char, int> map{{'(', 1},  {')', -1}, {'[', 2},
                             {']', -2}, {'{', 3},  {'}', -3}};

template <typename E>
class ArrayStack {
    enum { DEF_CAPACITY = 100 };  // default stack capacity
   public:
    ArrayStack(int cap = DEF_CAPACITY);  // constructor from capacity
    int size() const;                    // number of items in the stack
    bool empty() const;                  // is the stack empty?
    const E &top();                      // get the top element
    void push(const E &e);               // push element onto stack
    void pop();                          // pop the stack
                                         // ...housekeeping functions omitted
   private:                              // member data
    E *S;                                // array of stack elements
    int capacity;                        // stack capacity
    int t;                               // index of the top of the stack
};
template <typename E>  // push element onto the stack
void ArrayStack<E>::push(const E &e) {
    if (size() == capacity) cout << "Push to full stack\n";
    S[++t] = e;
}
template <typename E>  // pop the stack
void ArrayStack<E>::pop() {
    if (empty()) cout << "Pop from empty stack\n";
    --t;
}
template <typename E>
ArrayStack<E>::ArrayStack(int cap)
    : S(new E[cap]), capacity(cap), t(-1) {}  // constructor from capacity
template <typename E>
int ArrayStack<E>::size() const {
    return (t + 1);
}  // number of items in the stack

template <typename E>
bool ArrayStack<E>::empty() const {
    return (t < 0);
}  // is the stack empty?

template <typename E>  // return top of stack
const E &ArrayStack<E>::top() {
    if (empty()) cout << "Top of empty stack\n";
    return S[t];
}
// returns true if the given character is a bracket, false o.w.
bool isBracket(char c) {
    return c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']';
}

bool isBalanced(string expr) {
    ArrayStack<char> stack;

    for (int i = 0; i < expr.length(); i++) {
        char token = expr[i];
        if (!isBracket(token)) continue;

        switch (token) {
            case '(':
                stack.push('(');
                break;
            case ')':
                if (stack.empty() || stack.top() != '(')
                    return false;
                else
                    stack.pop();
                break;
            case '{':
                stack.push('{');
                break;
            case '}':
                if (stack.empty() || stack.top() != '{')
                    return false;
                else
                    stack.pop();
                break;
            case '[':
                stack.push('[');
                break;
            case ']':
                if (stack.empty() || stack.top() != '[')
                    return false;
                else
                    stack.pop();
                break;

            default:
                break;
        }
    }
    return stack.empty();
}

int main() {
    string expr[] = {
        "((a + b) * c + d - e) / (f + g) - (h + j) * k - 1 / (m - n)", "(()())",
        "()())", "()(())()"};

    for (int i = 0; i < 4; i++) {
        bool isBal = isBalanced(expr[i]);
        cout << expr[i] << ": ";

        if (isBal)
            cout << "Balanced" << endl;
        else
            cout << "Not balanced" << endl;
    }

    return 0;
}