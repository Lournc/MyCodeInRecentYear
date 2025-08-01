#include <iostream>
#include <string>

using namespace std;

string addBinary(string a, string b) {
  string res;
  res.resize(max(a.size(), b.size()) + 1);
  int m{}, p{(int)res.size() - 1};
  auto it1 = a.rbegin(), it2 = b.rbegin();
  for (; it1 != a.rend() && it2 != b.rend(); it1++, it2++) {
    int n = m + (*it1 - '0') + (*it2 - '0');
    if (n == 3) {
      m = 1;
      res[p--] = '1';
    } else if (n == 2) {
      m = 1;
      res[p--] = '0';
    } else {
      m = 0;
      res[p--] = n + '0';
    }
  }
  auto it = a.size() > b.size() ? it1 : it2;
  auto end = a.size() > b.size() ? a.rend() : b.rend();
  while (it != end) {
    int n = m + (*it - '0');
    if (n == 2) {
      m = 1;
      res[p--] = '0';
    } else {
      m = 0;
      res[p--] = n + '0';
    }
    it++;
  }
  if (p == 0 && m == 1) {
    res[0] = '1';
  }
  if (res[0] == 0) {
    return res.substr(1, res.size() - 1);
  }
  return res;
}

int main() {
  string a{"11"}, b{"1"};
  cout << addBinary(a, b);
  return 0;
}