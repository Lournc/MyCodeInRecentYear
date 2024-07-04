#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

void mergesort(std::vector<int> &data, int l, int r) {
  if (r <= l)
    return;
  mergesort(data, l, (l + r) / 2);
  mergesort(data, (l + r) / 2 + 1, r);
  int ll{l}, rr{(l + r) / 2 + 1};
  while (rr <= r) {
    if (data.at(ll) > data.at(rr)) {
      std::swap(data.at(ll), data.at(rr));
      for (int i = rr; i < r && data[i] > data[i + 1]; i++)
        std::swap(data[i], data[i + 1]);
    }
    ll++;
    if (ll == rr)
      rr++;
  }
}

int main() {
  std::vector<int> data{3,  17, 42, 8,  29, 55, 63, 12, 77, 34,
                        91, 48, 26, 59, 67, 14, 82, 36, 95, 44};

  mergesort(data, 0, data.size() - 1);
  for (auto &v : data) {
    std::cout << v << ' ';
  }
  return 0;
}