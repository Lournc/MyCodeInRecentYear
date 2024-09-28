#include <stdio.h>
int main() {
  char d;
  int a;
  float b;
  double c;
  scanf("%c,%d,%f,%lf", &d, &a, &b, &c);
  double e;
  e = a + b + c;
  printf("%c %.6lf\n", d, e);
  return 0;
}