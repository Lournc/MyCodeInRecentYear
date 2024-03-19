#include <iostream>
#include <type_traits>
#include <vector>
using namespace std;

template <typename T>
concept is_container = requires(T x) {
  std::begin(x);
  std::end(x);
};

int main() {
  cout << is_container<vector<int>>;
  return 0;
}