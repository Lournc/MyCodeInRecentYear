#include <algorithm>
#include <format>
#include <iostream>
#include <vector>

struct item {
  double w;
  double v;
};

int main() {
  std::vector<item> items{{35, 10}, {30, 40}, {60, 30}, {50, 50},
                          {40, 35}, {10, 40}, {25, 30}};
  double max{150};
  std::sort(items.begin(), items.end(),
            [](const item &a, const item &b) { return a.v / a.w > b.v / b.w; });
  std::pmr::vector<item> bag;
  for (int i = 0; i < items.size(); i++) {
    if (items[i].w <= max) {
      max -= items[i].w;
      bag.push_back(items[i]);
    }
  }
  for (int i = 0; i < bag.size(); i++) {
    std::cout << std::format("w:{} v:{}\n", bag[i].w, bag[i].v);
  }
  return 0;
}