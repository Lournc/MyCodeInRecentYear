#include <iostream>

int main() {
  int n;
  std::cin >> n;
  const int v = [&]() { return n; }();
  // v = 1; error
  // int arr[v]; warning: v is not a constant expression
  return 0;
}