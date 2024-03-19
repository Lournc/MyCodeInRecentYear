#include <deque>
#include <iostream>
using namespace std;
int num;
int main() {
  int n, k;
  cin >> n >> k;
  string str;
  cin >> str;
  deque<char> st;
  for (char &c : str) {
    while (k && st.size() && c > *st.rbegin()) {
      st.pop_back();
      k--;
    }
    st.push_back(c);
  }
  for (auto &c : st) {
    cout << c;
  }
  return 0;
}