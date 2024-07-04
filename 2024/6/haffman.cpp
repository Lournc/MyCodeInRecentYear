#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

// 定义哈夫曼树的节点
struct node {
  char ch;
  int freq;
  node *left;
  node *right;

  node(char ch, int freq, node *left = nullptr, node *right = nullptr)
      : ch(ch), freq(freq), left(left), right(right) {}
};

// 比较器，用于优先队列
struct compare {
  bool operator()(node *l, node *r) { return l->freq > r->freq; }
};

// 生成哈夫曼编码
void generate_codes(node *root, const string &str,
                    unordered_map<char, string> &huffman_code) {
  if (root == nullptr)
    return;

  // 叶子节点
  if (!root->left && !root->right) {
    huffman_code[root->ch] = str;
  }

  generate_codes(root->left, str + "0", huffman_code);
  generate_codes(root->right, str + "1", huffman_code);
}

// 递归删除哈夫曼树节点
void delete_tree(node *root) {
  if (root == nullptr)
    return;
  delete_tree(root->left);
  delete_tree(root->right);
  delete root;
}

// 主函数
int main() {
  string text;
  cout << "请输入要编码的文本：";
  getline(cin, text);

  // 统计字符频率
  unordered_map<char, int> freq;
  for (char ch : text) {
    freq[ch]++;
  }

  // 创建一个优先队列
  priority_queue<node *, vector<node *>, compare> pq;

  // 创建叶子节点并插入队列
  for (auto pair : freq) {
    pq.push(new node(pair.first, pair.second));
  }

  // 构建哈夫曼树
  while (pq.size() != 1) {
    node *left = pq.top();
    pq.pop();
    node *right = pq.top();
    pq.pop();

    int sum = left->freq + right->freq;
    pq.push(new node('\0', sum, left, right));
  }

  // 根节点
  node *root = pq.top();

  // 生成哈夫曼编码
  unordered_map<char, string> huffman_code;
  generate_codes(root, "", huffman_code);

  // 输出哈夫曼编码
  cout << "哈夫曼编码如下：\n";
  for (auto pair : huffman_code) {
    cout << pair.first << " " << pair.second << "\n";
  }

  // 编码数据
  string encoded_string;
  for (char ch : text) {
    encoded_string += huffman_code[ch];
  }

  cout << "\n编码后的字符串为：\n" << encoded_string << "\n";

  // 删除哈夫曼树以释放内存
  delete_tree(root);

  return 0;
}
