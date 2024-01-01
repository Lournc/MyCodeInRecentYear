#include <climits>
#include <iostream>
#include <string>
using namespace std;

struct TrieNode {
  int weight;
  int parent, lchild, rchild;
};
using HuffmanTree = TrieNode *;
using HuffmanCode = string **;
HuffmanCode HC;
HuffmanTree *HT;

void CreatHuffmanTree(int n);

void Select(int i, int &s1, int &s2);

void HuffmanCoding(int n);

int main() {
  int n;
  cout << "输入huffman树的项数:" << endl;
  cin >> n;
  CreatHuffmanTree(n);
  cout << "HuffmanTree:" << endl;
  for (int i = 1; i < 2 * n; i++) {
    cout << HT[i]->weight << " " << HT[i]->parent << " " << HT[i]->lchild << " "
         << HT[i]->rchild << endl;
  }

  HuffmanCoding(n);
  cout << "HuffmanCoding:" << endl;
  for (int i = 1; i <= n; i++) {
    cout << *HC[i] << endl;
    delete HC[i];
  }
  for (int i = 0; i < 2 * n; i++) {
    delete HT[i];
  }
  delete HC;

  delete[] HT;
  return 0;
}

void CreatHuffmanTree(int n) {
  int i;
  if (n <= 1) {
    return;
  }
  HT = new HuffmanTree[2 * n];
  cout << "逐个输入每个结点的权重:" << endl;
  HT[0] = new TrieNode;
  *HT[0] = {INT_MAX, 0, 0, 0};
  for (i = 1; i <= n; i++) {
    HT[i] = new TrieNode;
    int w;
    cin >> w;
    *HT[i] = {w, 0, 0, 0};
  }
  for (int i = n + 1; i < 2 * n; i++) {
    int s1, s2;
    Select(i - 1, s1, s2);
    HT[i] = new TrieNode;
    HT[s1]->parent = i;
    HT[s2]->parent = i;
    HT[i]->lchild = s1;
    HT[i]->rchild = s2;
    HT[i]->weight = HT[s1]->weight + HT[s2]->weight;
    HT[i]->parent = 0;
  }
}

void Select(int n, int &s1, int &s2) {
  s1 = 0;
  s2 = 0;
  for (int i = 1; i <= n; i++) {
    if (HT[i]->weight < HT[s1]->weight && HT[i]->parent == 0) {
      s1 = i;
    }
  }
  for (int i = 1; i <= n; i++) {
    if (HT[i]->weight < HT[s2]->weight && HT[i]->parent == 0 && i != s1) {
      s2 = i;
    }
  }
}

void HuffmanCoding(int n) {
  HC = new string *[n + 1];
  for (int i = 1; i <= n; i++) {
    string cd;
    cd.resize(n);
    cd[n - 1] = '\0';
    int start = n - 1;
    for (int c = i, f = HT[i]->parent; f != 0; c = f, f = HT[c]->parent) {
      if (HT[f]->lchild == c) {
        start--;
        cd[start] = '0';
      } else {
        start--;
        cd[start] = '1';
      }
    }
    HC[i] = new string;
    *HC[i] = cd;
  }
}
