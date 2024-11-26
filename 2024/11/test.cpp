#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int f(T v) {
  if constexpr (is_same_v<decltype(v), int>) {
    return 0;
  } else {
    return 1;
  }
}

constexpr int LEVEL[]{0, 4, 14, 114, 1114, 11114 /* 40GB */};

inline uint32_t GetLevel(uint32_t table_id, uint32_t total_table) {
  int max_level =
      std::lower_bound(LEVEL, LEVEL + sizeof(LEVEL) / 4, total_table) - LEVEL;
  int t = table_id + 1;
  for (int i = max_level; i > 0; i--) {
    t -= (LEVEL[i] - LEVEL[i - 1]);
    if (t <= 0) {
      return i - 1;
    }
  }
  return 0;
}

int main() {
  for (int i = 0; i < 13; i++) {
    cout << GetLevel(i, 13) << '\n';
  }
}