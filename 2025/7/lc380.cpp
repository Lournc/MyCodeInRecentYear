#include <bits/stdc++.h>

using namespace std;

class RandomizedSet {
  unordered_set<int> mapp;

public:
  RandomizedSet() {}

  bool insert(int val) {
    if (mapp.contains(val))
      return false;
    mapp.insert(val);
    return true;
  }

  bool remove(int val) {
    if (mapp.contains(val)) {
      mapp.erase(val);
      return true;
    }
    return false;
  }

  int getRandom() {
    auto size = mapp.size();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, size);
    int i{}, v1 = distrib(gen);
    for (auto &v : mapp) {
      if (++i == v1)
        return v;
    }
    return 0;
  }
};

int main() {
  RandomizedSet *obj = new RandomizedSet();
  bool param_1 = obj->insert(1);
  bool param_2 = obj->insert(5);
  bool param_3 = obj->insert(10);
  for (int i = 0; i < 30; i++)
    cout << obj->getRandom();
}