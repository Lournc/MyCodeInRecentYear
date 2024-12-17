#include <bits/stdc++.h>

using namespace std;

template <> struct std::hash<array<unsigned int, 26>> {
  size_t operator()(const array<unsigned int, 26> e) const {
    size_t res{};
    for (int i = 0; i < 26; i++) {
      if (1 & i)
        res |= e[i];
      else
        res ^= e[i];
    }
    return res;
  }
};

vector<vector<string>> groupAnagrams(vector<string> &strs) {
  vector<vector<string>> res;
  unordered_map<array<unsigned int, 26>, vector<string>> mapp;
  for (auto &s : strs) {
    array<unsigned int, 26> k{};
    for (auto c : s) {
      k[c - 'a']++;
    }
    mapp[k].push_back(std::move(s));
  }
  for (auto &[k, v] : mapp) {
    res.emplace_back(std::move(v));
  }
  return res;
}

int main() {
  vector<string> strs{"eat", "tea", "tan", "ate", "nat", "bat"};
  auto s = groupAnagrams(strs);
  for (auto &ss : s) {
    for (auto &sss : ss) {
      cout << sss << ' ';
    }
    cout << '\n';
  }
  return 0;
}