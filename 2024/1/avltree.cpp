#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <stack>
#include <stdexcept>
using uint = unsigned;
struct tree_node {
  int key_;
  int data_;
  uint r_level{};
  uint l_level{};
  tree_node(int key, int data) : key_(key), data_(data) {}
  std::shared_ptr<tree_node> p_node{nullptr};
  std::shared_ptr<tree_node> l_node{nullptr};
  std::shared_ptr<tree_node> r_node{nullptr};
};
class avltree {
  std::shared_ptr<tree_node> root{nullptr};
  void insert_helper(std::shared_ptr<tree_node> p_node,
                     std::shared_ptr<tree_node> i_node, uint lord = 0,
                     uint deep = 0);
  void remove_helper(int key, std::shared_ptr<tree_node> node, uint lord = 0,
                     uint deep = 0);
  bool find_helper(int key, int &ans, std::shared_ptr<tree_node> node);

  void ll_ave(std::shared_ptr<tree_node>);
  void lr_ave(std::shared_ptr<tree_node>);
  void rl_ave(std::shared_ptr<tree_node>);
  void rr_ave(std::shared_ptr<tree_node>);

  std::stack<std::shared_ptr<tree_node>> lord_;

public:
  void insert(int key, int data) {
    auto node = std::make_shared<tree_node>(key, data);
    insert_helper(root, node);
  }
  void remove(int key) { remove_helper(key, root); }
  int find(int key);
};

int main() {
  using std::cin;
  using std::cout;
  avltree tree;
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int a, b;
    cin >> a >> b;
    tree.insert(a, b);
  }
  cin >> n;
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    cout << tree.find(a) << ' ';
  }
  return 0;
}

int avltree::find(int key) {
  int ans;
  if (find_helper(key, ans, root)) {
    return ans;
  }
  throw std::runtime_error("The tree has no this key node\n");
}

bool avltree::find_helper(int key, int &ans, std::shared_ptr<tree_node> node) {
  if (node->key_ == key) {
    ans = node->data_;
    return true;
  }
  if (node->key_ > key && node->l_node.get()) {
    return find_helper(key, ans, node->l_node);
  }
  if (node->key_ < key && node->r_node.get()) {
    return find_helper(key, ans, node->r_node);
  }
  return false;
}

void avltree::insert_helper(std::shared_ptr<tree_node> p_node,
                            std::shared_ptr<tree_node> i_node, uint lord,
                            uint deep) {
  if (root.get() == nullptr) {
    root = i_node;
    return;
  }
  auto p_key = p_node->key_;
  auto i_key = i_node->key_;
  if (i_key > p_key) {
    lord <<= 1;
    lord += 1;
    if (p_node->r_node) {
      insert_helper(p_node->r_node, i_node, lord, deep + 1);
      return;
    }
    p_node->r_node = i_node;
    i_node->p_node = p_node;
    deep++;
  } else if (i_key < p_key) {
    lord <<= 1;
    if (p_node->l_node) {
      insert_helper(p_node->l_node, i_node, lord, deep + 1);
      return;
    }
    p_node->l_node = i_node;
    i_node->p_node = p_node;
    deep++;
  } else {
    p_node->data_ = i_node->data_;
    if (root->key_ == i_node->key_) {
      return;
    }
  }
  // 能走到这里说明已经插入完了，然后根据当前深度判断当前在左子树还是右子树
  // 大胆的用uint存lord是因为除非插入了40多亿的数据，不然递归层数肯定不超过32
  bool is_right = lord & (1 << (deep - 1));
  // 如果平衡被打破
  if (abs((int)r_level - (int)l_level) > 1) {
    uint temp = lord & 0x3;
    // ll = 0, lr = 1, rl = 2, rr = 3
    if (temp == 0) {
      ll_ave(i_node);
    } else if (temp == 1) {
      lr_ave(i_node);
    } else if (temp == 2) {
      rl_ave(i_node);
    } else {
      rr_ave(i_node);
    }
  }
}

void avltree::remove_helper(int key, std::shared_ptr<tree_node> node, uint lord,
                            uint deep) {
  if (key == root->key_ && r_level == 0 && l_level == 0) {
    root = std::make_shared<tree_node>(nullptr);
  }
}