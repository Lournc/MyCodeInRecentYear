#include <iostream>
#include <unordered_map>

using namespace std;

bool isIsomorphic(string s, string t) {
  unordered_map<char, int> m1, m2;
  m1[s[0]] = 1;
  m2[t[0]] = 1;
  for (int i = 1; i < s.size(); i++) {
    if (m1.contains(s[i])) {
      if (!m2.contains(t[i]) || !(m2[t[i]] == m1[s[i]])) {
        return false;
      }
    } else {
      m1[s[i]] = m1.size() + 1;
      if (!m2.contains(t[i])) {
        m2[t[i]] = m2.size() + 1;
      } else {
        return false;
      }
    }
  }
  return true;
}

int main() {
  cout << isIsomorphic("app", "coo");
  cout << isIsomorphic("love", "youu");
  return 0;
}