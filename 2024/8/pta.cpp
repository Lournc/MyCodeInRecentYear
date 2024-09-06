#include <stdio.h>
int main() {
  double a;
  scanf("%lf", &a);
  int e = a * 100;
  int t = e % 100;
  int b = a;
  int c[4];
  float d = a - b;
  c[1] = b % 60;
  b /= 60;
  c[2] = b % 60;
  b /= 60;
  c[3] = b % 24;
  printf("%02d:%02d:%02d.%02d", c[3], c[2], c[1], t);
  return 0;
}