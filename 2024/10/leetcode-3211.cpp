#include <iostream>
#include <string>
#include <vector>

void help(std::string &s, int n, std::vector<std::string> &res) {
  char c[]{'1', '0'};
  for (auto &v : c) {
    if (!s.empty() && v == '0' && *s.rbegin() == '0') {
      break;
    }
    s += v;
    if (s.size() == n) {
      res.push_back(s);
    } else {
      help(s, n, res);
    }
    s.pop_back();
  }
}

std::vector<std::string> validStrings(int n) {
  std::string s;
  std::vector<std::string> res;
  help(s, n, res);
  return res;
}

int main() {
  auto vec = validStrings(3);
  for (auto s : vec) {
    std::cout << s << '\n';
  }
  return 0;
}