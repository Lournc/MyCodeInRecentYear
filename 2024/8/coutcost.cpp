#include <ctime>
#include <format>
#include <iostream>

#define N 10000000
using namespace std;
int a[N];
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
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
    cout << i << " ";
  }
  /*==============测试=================*/
  // 结束计时
  end = clock();
  std::cout << std::format("\n测试完毕，{}个数据cout总共用时：{}秒\n", N,
                           (double)(end - start) / CLOCKS_PER_SEC);

  return 0;
}

/*
real    0m19.206s
user    0m2.758s
sys     0m1.012s

real    0m19.024s
user    0m2.741s
sys     0m1.047s

real    0m19.190s
user    0m2.566s
sys     0m1.225s
 */