#include <stdio.h>

int main() {
  int a, b = 10;
  scanf("%d", &a);
  printf("%d=%d", a, a % 10);
  a /= 10;
  while (a) {
    int c = a % 10;
    printf("+%d*%d", c, b);
    b *= 10;
    a /= 10;
  }
  return 0;
}