#include <fstream>
#include <iostream>
class Chars {
  std::string data_;

public:
  Chars() = default;
  Chars(const std::string data) : data_(data) {}
  Chars(Chars &other) : data_(other.data_) {}

  friend std::ostream &operator<<(std::ostream &os, Chars chars) {
    os << chars.data_;
    return os;
  }

  friend std::istream &operator>>(std::istream &is, Chars &chars) {
    is >> chars.data_;
    return is;
  }
};
int main() {
  std::fstream fs("test.txt", std::ios_base::in | std::ios_base::out);
  if (!fs) {
    std::fstream("test.txt", std::ios_base::out);
  }
  fs << "He";
  Chars v;
  std::string v2;
  fs.seekg(0);
  fs >> v;
}