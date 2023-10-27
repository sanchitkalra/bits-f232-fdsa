// leetcode: https://leetcode.com/problems/min-stack/

// logic is to maintain two stacks. One for normal stack operation, and one for
// maintaining the min element. Simple approach is to use a int variable to
// track min element but it cannot work reliably on popping elements.

#include <bits/stdc++.h>
using namespace std;

class MinStack {
   private:
    stack<int> st, min_st;

   public:
    MinStack() {}

    void push(int val) {
        st.push(val);
        if (!min_st.empty()) {
            val = min(val, min_st.top());
        }
        min_st.push(val);
    }

    void pop() {
        st.pop();
        min_st.pop();
    }

    int top() { return st.top(); }

    int getMin() { return min_st.top(); }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */