#include <ctime>
#include <iostream>

#define N 10000000
using namespace std;

int a[N];
int main() {
  int i;

  // 初始化测试数组
  for (i = 0; i < N; i++) {
    a[i] = i;
  }

  // 开始计时
  clock_t start, end;
  start = clock();
  /*==============测试=================*/
  for (i = 0; i < N; i++) {
    printf("%d ", i);
  }
  /*==============测试=================*/
  // 结束计时
  end = clock();
  printf("\n测试完毕，%d个数据printf总共用时：%lf秒\n", N,
         (double)(end - start) / CLOCKS_PER_SEC);

  return 0;
}

/*
real    0m19.008s
user    0m1.874s
sys     0m0.932s

real    0m19.316s
user    0m1.774s
sys     0m1.106s

real    0m19.274s
user    0m1.856s
sys     0m1.038s
*/