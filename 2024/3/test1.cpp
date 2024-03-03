#include <iostream>
#include <stack>

using namespace std;

class MyQueue {
private:
  stack<int> inStack, outStack;

  void in2out() {
    cout << "in2out\n";
    while (!inStack.empty()) {
      cout << "clock..\n";
      outStack.push(inStack.top());
      inStack.pop();
    }
  }

public:
  MyQueue() {}

  void push(int x) { inStack.push(x); }

  int pop() {
    cout << "pop\n";
    if (outStack.empty()) {
      in2out();
    }
    int x = outStack.top();
    outStack.pop();
    return x;
  }

  int peek() {
    cout << "peek\n";
    if (outStack.empty()) {
      in2out();
    }
    return outStack.top();
  }

  bool empty() { return inStack.empty() && outStack.empty(); }
};

int main() {
  MyQueue *obj = new MyQueue();
  for (int i = 0; i < 10; i++) {
    obj->push(i);
  }
  int param_2 = obj->pop();
  int param_3 = obj->peek();
  bool param_4 = obj->empty();
  obj->pop();
  obj->push(10);
  obj->pop();
  cout << param_2 << ' ' << param_3 << ' ' << param_4;
}