#include <algorithm>
#include <iostream>
#include <list>
#include <unordered_map>
#include <utility>

class LRU {
  std::unordered_map<int, std::list<std::pair<int, int>>::iterator> mapp;
  std::list<std::pair<int, int>> cache;
  // lru size
  int size;

public:
  LRU(int n) : size(n) {}

  bool Get(int k, int &v) {
    if (mapp.contains(k)) {
      v = mapp[k]->second;
      cache.erase(mapp[k]);
      cache.push_front(std::make_pair(k, v));
      mapp[k] = cache.begin();
      return true;
    } else {
      return false;
    }
  }

  void Insert(int k, int v) {
    if (mapp.contains(k)) {
      cache.erase(mapp[k]);
      cache.push_front(std::make_pair(k, v));
      mapp[k] = cache.begin();
    } else {
      if (cache.size() == size) {
        auto t = cache.rbegin();
        mapp.erase(t->first);
        cache.pop_back();
      }
      cache.push_front(std::make_pair(k, v));
      mapp[k] = cache.begin();
    }
  }
};

int main() {}