// // 创意数字匹配
// #include <iostream>
// #include <list>
// #include <string>
// #include <vector>

// std::string solution(int n, std::string titleTemplate,
//                      std::vector<std::string> titles) {
//   std::list<std::string> slice;
//   while (true) {
//     auto p1 = titleTemplate.find('{');
//     if (p1 == std::string::npos) {
//       slice.emplace_back(titleTemplate);
//       break;
//     }
//     auto p2 = titleTemplate.find('}', p1);
//     slice.emplace_back(titleTemplate.substr(0, p1));
//     titleTemplate = titleTemplate.substr(p2 + 1);
//   }
//   std::string ans;
//   for (auto &title : titles) {
//     int pos{1};
//     auto ite = slice.begin();
//     if (title.find(*ite) != 0 && *slice.begin() != "") {
//       ans += "False,";
//       continue;
//     }
//     while (++ite != --slice.end()) {
//       if ((pos = title.find(*ite, pos)) == std::string::npos) {
//         ans += "False,";
//         goto NotFound;
//       }
//     }
//     if (title.find(*--slice.end(), title.size() - ite->size() - 1) !=
//             title.size() - ite->size() &&
//         *ite != "") {
//       ans += "False,";
//       continue;
//     }
//     ans += "True,";
//   NotFound:;
//   }
//   ans.pop_back();
//   return ans;
// }

// int main() {
//   //  You can add more test cases here
//   std::vector<std::string> testTitles1 = {"adcdcefdfeffe", "adcdcefdfeff",
//                                           "dcdcefdfeffe", "adcdcfe"};
//   std::vector<std::string> testTitles2 = {
//       "CLSomGhcQNvFuzENTAMLCqxBdj", "CLSomNvFuXTASzENTAMLCqxBdj",
//       "CLSomFuXTASzExBdj",          "CLSoQNvFuMLCqxBdj",
//       "SovFuXTASzENTAMLCq",         "mGhcQNvFuXTASzENTAMLCqx"};
//   std::vector<std::string> testTitles3 = {"abcdefg", "abefg", "efg"};

//   std::cout << solution(4, "ad{xyz}cdc{y}f{x}e", testTitles1)
//             << (solution(4, "ad{xyz}cdc{y}f{x}e", testTitles1) ==
//                 "True,False,Fales,True")
//             << std::endl;
//   std::cout << (solution(6, "{xxx}h{cQ}N{vF}u{XTA}S{NTA}MLCq{yyy}",
//                          testTitles2) ==
//                          "False,False,Fales,False,Fales,True")
//             << std::endl;
//   std::cout << (solution(3, "a{bdc}efg", testTitles3) == "True,Trur,Fales")
//             << std::endl;

//   return 0;
// }

// SQL代码补全

// #include <algorithm>
// #include <iostream>
// #include <memory>
// #include <string>
// #include <string_view>
// #include <vector>

// struct TrieNode {
//   bool valid{};
//   std::vector<std::pair<char, std::shared_ptr<TrieNode>>> next_level_;
// };

// class Trie {
//   std::shared_ptr<TrieNode> root_;

//   void SamePrefixStringHelper(std::shared_ptr<TrieNode> node, std::string
//   &str,
//                               std::vector<std::string> &res) {
//     if (node->valid) {
//       res.push_back(str);
//     }
//     if (node->next_level_.empty()) {
//       return;
//     }
//     for (auto &[c, ptr] : node->next_level_) {
//       str += c;
//       SamePrefixStringHelper(ptr, str, res);
//       str.pop_back();
//     }
//   }

// public:
//   Trie() : root_(std::make_shared<TrieNode>()) {}

//   std::vector<std::string> SamePrefixString(std::string_view source) {
//     std::shared_ptr<TrieNode> node = root_;
//     for (auto &c : source) {
//       auto &next_level = node->next_level_;
//       if (auto &&ite =
//               std::find_if(next_level.begin(), next_level.end(),
//                            [&](auto &pair) { return pair.first == c; });
//           ite != next_level.end()) {
//         node = ite->second;
//       } else {
//         return {};
//       }
//     }
//     std::vector<std::string> res{};
//     std::string str{source};
//     SamePrefixStringHelper(node, str, res);

//     return res;
//   }

//   void Insert(std::string_view source) {
//     std::shared_ptr<TrieNode> node = root_;
//     for (auto &c : source) {
//       auto &next_level = node->next_level_;
//       if (auto &&ite =
//               std::find_if(next_level.begin(), next_level.end(),
//                            [&](auto &pair) { return pair.first == c; });

//           ite != next_level.end()) {
//         node = ite->second;
//       } else {
//         auto &[_, ptr] =
//             next_level.emplace_back(c, std::make_shared<TrieNode>());
//         node = ptr;
//       }
//     }
//     node->valid = true;
//   }
// };

// std::string solution(int num, std::vector<std::string> data,
//                      std::string input) {
//   Trie trie;
//   for (auto &s : data) {
//     trie.Insert(s);
//   }
//   auto res_v = trie.SamePrefixString(input);
//   std::string s;
//   for (auto &ss : res_v) {
//     s += ss + ',';
//   }
//   if (s.empty()) {
//     s = "-1";
//   } else {
//     s.pop_back();
//   }
//   return s;
// }

// int main() {
//   //  You can add more test cases here
//   std::vector<std::string> testData1 = {
//       "select",          "from",    "where",      "limit", "origin_log_db",
//       "event_log_table", "user_id", "from_mobile"};
//   std::vector<std::string> testData2 = {
//       "select",    "from",    "where",      "limit",   "group", "having",
//       "in",        "index",   "inner",      "insert",  "like",  "log_db",
//       "log_table", "user_id", "group_name", "group_id"};

//   std::cout << (solution(8, testData1, "f") == "from,from_mobile") <<
//   std::endl; std::cout << (solution(16, testData2, "g") ==
//   "group,group_name,group_id")
//             << std::endl;
//   std::cout << (solution(16, testData2, "m") == "-1") << std::endl;

//   return 0;
// }
