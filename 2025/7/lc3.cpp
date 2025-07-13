#include <iostream>
#include <unordered_map>

using namespace std;

int lengthOfLongestSubstring(string s) {
  unordered_map<char, int> mapp;
  int res{};
  int j{};
  for (int i = 0; i < s.size(); i++) {
    char c = s[i];
    if (mapp.contains(c)) {
      while (s[j] != c && j < i) {
        mapp.erase(s[j]);
        j++;
      }
      if (j < i && s[j] == c)
        j++;
      mapp.erase(c);
    }
    mapp[c]++;
    res = max(res, i - j + 1);
  }
  return res;
}

int main() {
  cout << lengthOfLongestSubstring("tmmzuxt");
  return 0;
}