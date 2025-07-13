#include <bits/stdc++.h>

using namespace std;

int minSubArrayLen(int target, vector<int> &nums) {
  int total{nums[0]}, j{}, res{}, i{1};
  if (total >= target) {
    return 1;
  }
  while (i < nums.size() || total >= target) {
    if (total >= target) {
      bool f{};
      if (total - nums[j] >= target) {
        total -= nums[j++];
        f = true;
      }
      if (res != 0)
        res = min(res, i - j);
      else
        res = i - j;
      if (f)
        continue;
      else if (i == nums.size())
        break;
    }
    total += nums[i++];
  }
  return res;
}

int main() {
  vector<int> nums{1, 2, 3, 4, 5};
  cout << minSubArrayLen(15, nums);
  return 0;
}