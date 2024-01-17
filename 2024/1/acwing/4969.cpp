#include <iostream>
#include <stack>
#include <string>
using namespace std;

unsigned count(string &str) {
  unsigned ans{};
  for (int i = 0; i < str.size() - 1; i++) {
    if (str[i] == str[i + 1]) {
      ans++;
      i++;
    }
  }
  return ans;
}

int main() {
  string str;
  str.resize(2);
  cin >> str;
  stack<char> st;
  st.push(str[0]);
  int num{};
  for (char &v : str) {
    if (v == '?') {
      v = num & 1 ? st.top() : str[std::min(str.find('?') + 1, str.size() - 1)];
      if (v == '?') {
        v = str[std::min(str.find('?') + 1, str.size() - 1)] = '0';
        st.push('0');
      }
    } else if (v != st.top()) {
      st.push(v);
      num = 0;
    }
    num++;
  }
  cout << count(str);
  return 0;
}