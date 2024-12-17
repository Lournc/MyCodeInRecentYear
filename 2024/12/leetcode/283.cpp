#include <bits/stdc++.h>
#include <cstring>

using namespace std;

void moveZeroes(vector<int> &nums) {
  int s = nums.size();
  int idx{};
  for (int i = 0; i < s; i++) {
    if (nums[i] == 0) {
      continue;
    }
    nums[idx++] = nums[i];
  }
  memset(nums.data() + idx, 0, 4 * (s - idx));
}

int main() {
  vector<int> nums{0, 1, 0, 3, 12};
  moveZeroes(nums);
  for (auto v : nums) {
    cout << v << ' ';
  }
  return 0;
}