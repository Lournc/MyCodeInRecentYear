#include <iostream>
#include <string>
using namespace std;

struct Student {
  // 姓名
  string name;
  // 年龄
  int age;
  // 分数
  int score;
};

int main() {
  Student s = {"张三", 18, 100}; // struct可以省略

  Student *p = &s;

  p->score = 80;

  cout << "姓名: " << p->name << " 年龄: " << p->age << " 分数: " << p->score
       << endl;

  return 0;
}