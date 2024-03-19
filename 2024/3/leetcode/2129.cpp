#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
  static string capitalizeTitle(string title) {
    string ans, word;
    stringstream stream;
    stream << title;
    while (stream >> word) {
      transform(
          word.begin(), word.end(), word.begin(),
          [](unsigned char c) -> unsigned char { return std::tolower(c); });
      if (word.size() > 2) {
        word[0] = toupper(word[0]);
      }
      ans += word + ' ';
    }
    ans.erase(ans.size() - 1);
    return ans;
  }
};

int main() {
  string title{"rEd BlOoD ceLleR FoREvEr"};
  cout << Solution::capitalizeTitle(title);
  return 0;
}