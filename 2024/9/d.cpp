#include <bits/stdc++.h>

namespace a {
class vector {
public:
  int a;
};
} // namespace a

namespace b {
class vector {
public:
  int b;
};
} // namespace b

int main() {
  a::vector a;
  a.a = 10;
  std::cout << a.a;
  return 0;
}
