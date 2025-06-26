#include <iostream>
#include <memory>
#include <set>

struct list_node {
  int data_{};
  std::shared_ptr<list_node> next_{nullptr};
  list_node() = default;
  list_node(int data) : data_(data) {}
};

class List {
  int size_{};
  std::shared_ptr<list_node> head_;
  std::shared_ptr<list_node> tail_;

public:
  List() : head_(std::make_shared<list_node>()) {}
  void PushBack(int v) {
    if (size_ == 0) {
      head_->next_ = std::make_shared<list_node>(v);
      tail_ = head_->next_;
    } else {
      tail_->next_ = std::make_shared<list_node>(v);
      tail_ = tail_->next_;
    }
    size_++;
  }
  std::shared_ptr<list_node> Begin() { return head_->next_; }
};

int main() {
  List list;
  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    int v;
    std::cin >> v;
    list.PushBack(v);
  }
  std::set<int> s;
  auto t = list.Begin();
  auto t2 = t;
  for (int i = 0; i < n; i++) {
    int v = t->data_;
    bool b{};
    // s 包含v需要移除节点, t是当前节点, t2为t上一个节点
    if (s.contains(v)) {
      t2->next_ = t->next_;
      b = true;
    } else {
      s.insert(v);
    }
    t = t->next_;
    if (!b && i != 0) {
      t2 = t2->next_;
    }
  }
  t = list.Begin();
  while (t != nullptr) {
    std::cout << t->data_ << ' ';
    t = t->next_;
  }
}