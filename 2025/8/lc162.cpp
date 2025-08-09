#include <bits/stdc++.h>

using namespace std;

class Solution {
  int helper(vector<int> &nums, int l, int r) {
    if (l == r) {
      return l;
    }
    int p = (l + r) / 2;
    if (p == l && nums[p] > nums[p + 1]) {
      return p;
    }
    if (p == l) {
      return p + 1;
    }
    if (nums[p] > nums[p + 1] && nums[p] > nums[p - 1]) {
      return p;
    }
    if (nums[p + 1] > nums[p - 1]) {
      return helper(nums, p + 1, r);
    }
    return helper(nums, l, p - 1);
  }

public:
  int findPeakElement(vector<int> &nums) {
    int l{}, r{(int)nums.size() - 1};
    return helper(nums, l, r);
  }
};