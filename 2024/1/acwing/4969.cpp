#include <iostream>
#include <string>
using namespace std;

unsigned count(string &str) {
  unsigned ans{};
  for (int i = 0; i < str.size() - 2; i++) {
    if (str[i] == str[i + 1] || str[i] == '?' || str[i + 1] == '?') {
      ans++;
      i++;
    }
  }
  return ans;
}

int main() {
  string str;
  cin >> str;
  cout << count(str);
  return 0;
}