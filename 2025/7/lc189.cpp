#include <bits/stdc++.h>
#include <cstring>
#include <vector>
using namespace std;

class Solution {
public:
  void rotate(vector<int> &nums, int k) {
    k = k % nums.size();
    int *data = nums.data();
    int *t = new int[nums.size()];
    memcpy(t, data + nums.size() - k, k * 4);
    memcpy(t + k, data, (nums.size() - k) * 4);
    memcpy(data, t, nums.size() * 4);
    delete[] t;
  }
};

int main() {
  vector<int> nums{1, 2, 3, 4, 5, 6, 7};
  Solution s;
  s.rotate(nums, 3);
  for (int &n : nums) {
    cout << n << ' ';
  }
  return 0;
}