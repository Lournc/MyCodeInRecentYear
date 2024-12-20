#include <algorithm>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <string>
#include <string_view>

using namespace std;

int minAnagramLength(string s) {
  int size{static_cast<int>(s.size())}, res{size};
  for (size_t i = 1; i < size; i++) {
    if (size % i == 0) {
      int arr[26]{};
      string_view sub{s.data(), i};
      for (auto &c : sub) {
        arr[c - 'a']++;
      }
      bool done{true};
      for (int j = i; j < size; j += i) {
        int t[26];
        memcpy(t, arr, 4 * 26);
        string_view sv{s.data() + j, i};
        for (auto &c : sv) {
          t[c - 'a']--;
        }
        if (!std::all_of(t, t + 26, [&](int v) { return v == 0; })) {
          done = false;
          break;
        }
      }
      if (done) {
        return i;
      }
    }
  }
  return res;
}

int main() {
  cout << minAnagramLength("jjj");
  return 0;
}