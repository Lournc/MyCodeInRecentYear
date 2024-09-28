// 7-1
// #include <iostream>
// int main() {
//   int n;
//   int arr[21]{};
//   std::cin >> n;
//   for (int i = 0; i < n; i++) {
//     std::cin >> arr[i];
//     std::cout << ' ' << arr[i];
//   }
//   std::cout << std::endl;
//   for (int i = n - 1; i > -1; i--) {
//     std::cout << ' ' << arr[i];
//   }
//   return 0;
// }

// 7-2
// #include <algorithm>
// #include <functional>
// #include <iomanip>
// #include <ios>
// #include <iostream>
// #include <vector>
// int main() {
//   std::vector<double> a, b;
//   int n;
//   std::cin >> n;
//   for (int i = 0; i < n; i++) {
//     double c, d;
//     std::cin >> c >> d;
//     a.push_back(c);
//     b.push_back(d);
//   }
//   std::sort(a.begin(), a.end());
//   std::sort(b.begin(), b.end(), std::greater<double>());
//   for (int i = 0; i < n; i++)
//     std::cout << std::fixed << std::setprecision(2) << a[i] << ' ' << b[i]
//               << '\n';
//   return 0;
// }

// 7-3
// #include <algorithm>
// #include <iostream>
// #include <vector>

// int main() {
//   std::vector<int> a(20);
//   int b{1}, i{};
//   while (true) {
//     scanf("%d", &b);
//     if (b == 0)
//       break;
//     a[i++] = b;
//   }
//   while (true) {
//     scanf("%d", &b);
//     if (b == 0)
//       break;
//     a[i++] = b;
//   }
//   std::sort(a.begin(), a.end());
//   a.erase(std::remove(a.begin(), a.end(), 0), a.end());
//   for (int &v : a) {
//     std::cout << v << ' ';
//   }
//   return 0;
// }

// 7-4
// #include <algorithm>
// #include <iostream>
// using namespace std;
// int main() {
//   int n[6][6]{};
//   int i;
//   int c = 0;
//   bool have = false;
//   cin >> i;
//   for (int a = 0; a < i; a++)
//     for (int b = 0; b < i; b++)
//       cin >> n[a][b];
//   for (int a = 0; a < i; a++) {
//     c = max_element(&n[a][0], &n[a][i]) - &n[a][0];
//     for (int b = 0; b < i; b++) {
//       int q = 0;
//       if (n[a][b] == n[a][c]) {
//         for (int l = 0; l < i; l++) {
//           if (n[l][b] >= n[a][b])
//             q++;
//         }
//         if (q == i) {
//           cout << "(" << a << "," << b << ")" << endl;
//           have = true;
//         }
//       }
//     }
//   }
//   if (have == false)
//     cout << "NONE";
// }

// 7-5
// #include <cstdio>
// #include <iostream>
// int is_lei(char c) { return c == '*'; }
// int lei(char arr[17][17], int x, int y) {
//   int res{};
//   res = is_lei(arr[x - 1][y - 1]) + is_lei(arr[x - 1][y]) +
//         is_lei(arr[x - 1][y + 1]) + is_lei(arr[x][y + 1]) +
//         is_lei(arr[x][y - 1]) + is_lei(arr[x + 1][y + 1]) +
//         is_lei(arr[x + 1][y]) + is_lei(arr[x + 1][y - 1]);
//   return res;
// }

// int main() {
//   int i;
//   std::cin >> i;
//   while (i--) {
//     char arr[17][17]{};
//     int m, n;
//     std::cin >> m >> n;
//     for (int i = 1; i <= m; i++) {
//       getchar();
//       for (int j = 1; j <= n; j++) {
//         arr[i][j] = getchar();
//       }
//     }
//     for (int i = 1; i <= m; i++) {
//       for (int j = 1; j <= n; j++) {
//         if (arr[i][j] == '*')
//           std::cout << '*';
//         else
//           std::cout << lei(arr, i, j);
//       }
//       std::cout << '\n';
//     }
//     if (i)
//       std::cout << '\n';
//   }
//   return 0;
// }

// 7-6
#include <iostream>
#include <map>
std::map<int, int> mapp{{6, 10000}, {16, 72},   {7, 36},   {17, 180},
                        {8, 720},   {18, 119},  {9, 360},  {19, 36},
                        {10, 80},   {20, 306},  {11, 252}, {21, 1080},
                        {12, 108},  {22, 144},  {13, 72},  {23, 1800},
                        {14, 54},   {24, 3600}, {15, 180}};

int main() {
  int n[5][5];
  for (int i = 1; i < 4; i++)
    for (int j = 1; j < 4; j++)
      std::cin >> n[i][j];

  return 0;
}

// 7-7
// #include <iostream>
// #include <string>

// int main() {
//   int n;
//   std::string s;
//   std::cin >> n >> s;
//   std::cout << s.substr(s.size() - n % s.size())
//             << s.substr(0, s.size() - n % s.size());
//   return 0;
// }

// 7-8
// #include <algorithm>
// #include <iostream>
// #include <map>
// char to_uppercase(unsigned char c) { return std::toupper(c); }
// int main() {
//   std::string s;
//   std::cin >> s;
//   std::transform(s.begin(), s.end(), s.begin(), to_uppercase);
//   std::map<char, int> total;
//   total['G'] = std::count(s.begin(), s.end(), 'G');
//   total['P'] = std::count(s.begin(), s.end(), 'P');
//   total['L'] = std::count(s.begin(), s.end(), 'L');
//   total['T'] = std::count(s.begin(), s.end(), 'T');
//   while (total['G'] + total['P'] + total['L'] + total['T']) {
//     if (total['G']) {
//       std::cout << 'G';
//       total['G']--;
//     }
//     if (total['P']) {
//       std::cout << 'P';
//       total['P']--;
//     }
//     if (total['L']) {
//       std::cout << 'L';
//       total['L']--;
//     }
//     if (total['T']) {
//       std::cout << 'T';
//       total['T']--;
//     }
//   }
//   return 0;
// }

// 7-9
// #include <iostream>
// #include <string>

// int main() {
//   int n;
//   char c;
//   std::cin >> n >> c;
//   getchar();
//   std::string s;
//   std::getline(std::cin, s);
//   if (s.size() < n) {
//     std::string t(n - s.size(), c);
//     std::cout << t << s;
//   } else {
//     std::cout << s.substr(s.size() - n);
//   }
//   return 0;
// }

// 7-10
// #include <algorithm>
// #include <iostream>
// #include <string>
// #include <vector>
// using namespace std;
// int main() {
//   vector<string> words;
//   string word;
//   while (cin >> word)
//     words.push_back(word);
//   if (words.empty())
//     return 0;
//   cout << *(words.end() - 1);
//   words.pop_back();
//   reverse(words.begin(), words.end());
//   for (string s : words) {
//     cout << ' ' << s;
//   }
// }