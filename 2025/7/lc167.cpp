#include <bits/stdc++.h>
using namespace std;

vector<int> twoSum(vector<int> &numbers, int target) {
  int l{}, r{(int)numbers.size() - 1};
  while (true) {
    if (numbers[l] + numbers[r] > target)
      r--;
    else if (numbers[l] + numbers[r] < target)
      l++;
    else
      return {l + 1, r + 1};
  }
  return {l + 1, r + 1};
}

int main() {
  vector<int> nums{2, 7, 11, 15};
  vector<int> res = twoSum(nums, 9);
  cout << res[0] << ' ' << res[1];
  return 0;
}