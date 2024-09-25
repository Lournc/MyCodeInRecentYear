#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
// filter_view 的定义
template <typename Iter, typename Func> class filter_view {
  Iter begin_;
  Iter end_;
  Func func_;

public:
  filter_view(Iter begin, Iter end, Func func)
      : begin_(begin), end_(end), func_(func) {}
  struct Iterator {
    Iter ite_;
    Iter end_;
    Func func_;
    Iterator &operator++() {
      ite_++;
      if (ite_ != end_)
        while (this->func_(*ite_))
          ite_++;
      return *this;
    }

    int operator*() { return *ite_; }

    friend bool operator==(Iterator &l, Iterator &r) {
      return l.ite_ == r.ite_ && l.func_ == r.func_;
    }
  };

  Iterator begin() { return {begin_, end_, func_}; }
  Iterator end() { return {end_, end_, func_}; }
};
int main() {
  vector v{1, 2, 3, 4, 5};
  auto &&fv = filter_view(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
  cout << accumulate(fv.begin(), fv.end(), 0) << endl;
}
