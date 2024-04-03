#include <iostream>
#include <ostream>
#include <vector>

class A {
public:
  A();
  A(int data) : data_(data) {}
  A operator+(const A &other) { return A(data_ + other.data_); };

  int data_{};
};

template <typename T>
concept have_operatoradd = requires(T a) { a + a; };
template <typename T> T add(T a, T b) {
  T ans;
  for (auto &v : a) {
    ans.push_back(v);
  }
  for (auto &v : b) {
    ans.push_back(v);
  }
  return ans;
}

template <have_operatoradd T> T add(T a, T b) { return T(a + b); }

std::ostream &operator<<(std::ostream &os, const std::vector<int> &a) {
  for (auto &v : a) {
    os << v << ' ';
  }
  return os;
}
std::ostream &operator<<(std::ostream &os, const A a) {
  os << a.data_ << ' ';
  return os;
}
int main() {
  std::vector<int> a{6}, b{1};
  A c{4}, d{3};
  int e{3}, f{7};
  std::cout << add(a, b) << add(c, d) << add(e, f);
  return 0;
}