#include <format>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  // 名称和单价
  vector<pair<string, double>> data{{"", 0},
                                    {"可口可乐", 3.5},
                                    {"德芙巧克力", 6.8},
                                    {"飘柔洗发水", 29.9},
                                    {"香蕉", 6.5},
                                    {"海天酱油", 9.9}};
  vector<int> num(data.size(), 0);
  while (true) {
    cout << "以下是商品列表请按序号选择商品操作:\n";
    for (int i = 1; i < data.size(); i++) {
      auto &[name, price] = data[i];
      cout << format("{}) {} {}\n", i, name, price);
    }
    cout << "输入商品序号以及购买数量(输入 0 退出): ";
    int c, n;
    cin >> c;
    if (c == 0) {
      break;
    }
    cin >> n;
    num[c] += n;
  }
  cout << "购买数量:\n";
  double total{};
  for (int i = 1; i < data.size(); i++) {
    cout << format("{} {}", data[i].first, num[i]);
    total += num[i] * data[i].second;
  }
  cout << "共需要支付: " << total;
}