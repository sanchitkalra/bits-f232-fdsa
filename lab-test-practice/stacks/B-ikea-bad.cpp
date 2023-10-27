// leetcode: https://leetcode.com/problems/next-greater-element-ii/

// the key here is to understand that we're in a circular array and the NGR
// element will be either to the right of our element (classic NGR) or to the
// left (circular right after the nth element). now first add all elements from
// the beginning of the array into our stack to simulate the case where the NGR
// is towards the left. The top of the stack must be the index 0 because for the
// last element in a circular fashion, the 0th element is the closest element.
// Now once we have the stack setup, we start traversing the given array for
// NGRs from the end of the array. We keep popping elements off the stack (while
// it has any) if they're smaller than or equal to the current element. Next, we
// check if the stack is empty, if so, we append -1. Otherwise, we calculate the
// distance using a simple logic: "st.top() - i". This assumes that if the NGR
// element is to the right, we'll get a positive value and can straightaway say
// that it is the NGR's index and if it is negative, we can say that the NGR's
// index is towards the left and we need to add n (no of elements) to make it
// the correct circular distance.

#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        stack<int> st;
        int n = nums.size() - 1;

        int i = n;
        while (i >= 0) {
            st.push(i);
            i--;
        }

        vector<int> ans;
        vector<int> dist;

        i = n;
        while (i >= 0) {
            while (!st.empty() && nums[st.top()] <= nums[i]) st.pop();

            if (st.empty()) {
                ans.push_back(-1);
                dist.push_back(-1);
            } else {
                ans.push_back(nums[st.top()]);
                int t = st.top() - i;
                dist.push_back(t >= 0 ? t : (t + n + 1));
            }

            st.push(i);
            i--;
        }

        reverse(ans.begin(), ans.end());
        reverse(dist.begin(), dist.end());

        for (auto x : dist) cout << x << " ";

        return ans;
    }
};