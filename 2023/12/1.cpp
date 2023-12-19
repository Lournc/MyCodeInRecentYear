#include "multi_threaded_sort.hpp"
#include <cstdio>
#include <iostream>
#include <queue>
#include <stdio.h>
#include <string>
#include <thread>
#include <vector>
#include <algorithm>
#define pFileSize 31
#define SINGLE_SIZE 25000000
#define ARR_SIZE 750000000
using PII = std::pair<int, int>;
std::vector<FILE *> pf(pFileSize);
int *arr;
void read_func(std::vector<std::thread> &threads) {
  // lambda函数为线程中读取文件的函数
  auto read_func = [&](int id) {
    std::string name = "data";
    name += std::to_string(id);
    name += ".txt";
    pf[id] = fopen(name.c_str(), "r+");
    // 分段读取文件到arr数组 为接下来排序做准备
    for (int i = (id - 1) * SINGLE_SIZE; i < id * SINGLE_SIZE; i++) {
      fscanf(pf[id], "%d", &arr[i]);
    }
    std::cout << name << std::endl;
    fclose(pf[id]);
  };
  for (int id = 0; id < 30; ++id) {
    // 将30个线程加入到vector中并设置线程id
    threads.emplace_back(read_func, id + 1);
  }
  for (auto &thread : threads) {
    // 执行线程中的函数读取文件中的数据
    thread.join();
  }
  std::cout << "read finished!" << '\n';
}
int main() {

  arr = new int[ARR_SIZE];

  std::vector<std::thread> threads;
  read_func(threads);
  
  multi_threaded_sort<int>(arr, ARR_SIZE, 16);

  std::priority_queue<PII, std::vector<PII>, std::greater<PII>> heap;
  FILE *pf_;
  pf_ = fopen("data.txt", "w+");
  std::cout << "前五十个最小的数字是:\n";
  for (int i = 0; i < ARR_SIZE; i++) {
    if (i < 50) {
     std::cout << arr[i] << ' '; 
      if (i + 1 % 10 == 0 ) {
        std::cout << std::endl;
      }
    } 
    if (arr[i] == arr[i + 1] && i < ARR_SIZE - 1) {
      int j = i;
      while (j < ARR_SIZE && arr[j] == arr[j + 1]) {
        fprintf(pf_, "%d ", arr[j]);
        j++;
      }
      int cnt = j - i + 1;
      i = j;
      if (heap.size() < 10) {
        heap.push({cnt, arr[i]});
        continue;
      }
      auto it = heap.top();
      if (cnt > it.first) {
        heap.pop();
        heap.push({cnt, arr[i]});
      }
    }
    fprintf(pf_, "%d ", arr[i]);
    if (i % 5000) {
      fprintf(pf_, "\n");
    }
  }
  std::cout << std::endl;
  std::cout << "出现次数最多的前10个数字是:" << std::endl;
  while (!heap.empty()) {
    std::cout << heap.top().second << "出现" << heap.top().first << "次"
              << std::endl;
    heap.pop();
  }
  return 0;
}