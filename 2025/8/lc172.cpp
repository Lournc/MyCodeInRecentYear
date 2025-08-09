
int trailingZeroes(int n) {
  int a{};
  int num{n};
  while (num > 0) {
    a += num / 5;
    num /= 5;
  }
  return a;
}