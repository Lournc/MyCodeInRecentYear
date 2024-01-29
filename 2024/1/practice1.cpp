#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
// filter_view 的定义
template <typename Iter, typename Func> class filter_view {
  Iter begin_;
  Iter end_;
  Func func_;
  class Iterator {

  };

public:
  filter_view(Iter begin, Iter end, Func func)
      : begin_(begin), end_(end), func_(func) {}
      
};
int main() {
  vector v{1, 2, 3, 4, 5};
  auto &&fv = filter_view(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
  cout << accumulate(fv.begin(), fv.end(), 0) << endl;
}
