#include <stdio.h>

int main() {
  double a = 235.7;
  int b = (int)(a * 100) % 100;
  printf("%d", b);
}