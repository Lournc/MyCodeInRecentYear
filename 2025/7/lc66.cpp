#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

vector<int> plusOne(vector<int> &digits) {
  vector<int> res(digits.size() + 1);
  int f{1};
  for (int i = 0; i < digits.size(); i++) {
    int n = digits[digits.size() - 1 - i] + f;
    res[i] = n % 10;
    f = n / 10;
  }
  res[digits.size()] = f;
  if (!*res.rbegin()) {
    res.pop_back();
  }
  reverse(res.begin(), res.end());
  return res;
}

int main() {
  vector<int> digits{9};
  auto res = plusOne(digits);
  for (auto n : res) {
    cout << n;
  }
  return 0;
}