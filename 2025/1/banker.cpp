#include <algorithm>
#include <format>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class BankerAlgorithm {
  int pro_num;
  int resource_num;
  std::vector<int> avaliable; // 当前各资源的数量
  std::map<int, std::string> resource_name;
  std::map<std::string, std::vector<int>> max; // 当前进程需要的最大资源量
  std::map<std::string, std::vector<int>> need; // 当前进程还需要的各类资源量
  std::map<std::string, std::vector<int>>
      allocation; // 当前进程已分配的各资源的量

  bool IsSafe(std::vector<bool> &finish,
              std::vector<std::string> &safe_sequence) {
    std::vector<int> work(avaliable);
    int count = 0;
    while (count < pro_num) {
      bool find = false;
      int i = 0;
      for (auto &[name, arr] : need) {
        if (!finish[i]) {
          bool flag = true;
          for (int j = 0; j < resource_num; j++) {
            if (arr[j] > work[j]) {
              flag = false;
              break;
            }
          }
          if (flag) {
            for (int j = 0; j < resource_num; j++) {
              work[j] += allocation[name][j];
            }
            finish[i] = true;
            count++;
            find = true;
            safe_sequence.push_back(name);
            break;
          }
        }
        i++;
      }
      if (!find) {
        return false;
      }
    }
    return true;
  }

public:
  void InitAllData() {
    // 清理所有数据
    {
      pro_num = 0;
      resource_num = 0;
      avaliable.clear();
      resource_name.clear();
      max.clear();
      need.clear();
      allocation.clear();
    }
    std::cout << "输入进程数和资源数：\n";
    std::cin >> pro_num >> resource_num;
    avaliable = std::vector<int>(resource_num);
    std::cout << "输入进程名：\n";
    for (int i = 0; i < pro_num; i++) {
      std::string name;
      std::cin >> name;
      max.emplace(name, std::vector<int>(resource_num));
      need.emplace(name, std::vector<int>(resource_num));
      allocation.emplace(name, std::vector<int>(resource_num));
    }
    std::cout << "输入资源名以及对应资源数：\n";
    for (int i = 0; i < resource_num; i++) {
      std::string name;
      int n;
      std::cin >> name >> n;
      avaliable[i] = n;
      resource_name[i] = name;
    }
    // 获取每个进程对应的max数组
    std::cout << "输入进程名以及对应的 max 数组：\n";
    for (int i = 0; i < pro_num; i++) {
      std::string name;
      std::cin >> name;
      for (int j = 0; j < resource_num; j++) {
        std::cin >> max[name][j];
      }
    }
    // 获取每个进程对应的allocation数组
    std::cout << "输入进程名以及对应的 allocation 数组：\n";
    for (int i = 0; i < pro_num; i++) {
      std::string name;
      std::cin >> name;
      for (int j = 0; j < resource_num; j++) {
        std::cin >> allocation[name][j];
      }
    }
  }

  void UpdateResourceForProcess() {
    std::string name;
    std::cout << "输入要添加资源的进程名：\n";
    std::cin >> name;
    if (max.find(name) == max.end()) {
      std::cout << "该进程不存在\n";
      return;
    }
    auto original_max = max[name];
    auto original_need = need[name];
    auto original_allocation = allocation[name];
    auto &max_data = max[name];
    auto &need_data = need[name];
    auto &allocation_data = allocation[name];
    std::cout << "输入更新的资源名以及数量(输入 -1 结束输入)：\n";
    while (true) {
      int n;
      std::cin >> name;
      if (name == "-1") {
        break;
      }
      std::cin >> n;
      if (auto it = std::find_if(resource_name.begin(), resource_name.end(),
                                 [&](auto &kv) { return kv.second == name; });
          it != resource_name.end()) {
        max_data[it->first] = n;
        need_data[it->first] = n;
      } else {
        std::cout << "该资源不存在\n";
      }
    }
    std::cout << "输入已分配的资源名以及数量(输入 -1 结束输入)：\n";
    while (true) {
      int n;
      std::cin >> name;
      if (name == "-1") {
        break;
      }
      std::cin >> n;
      if (auto it = std::find_if(resource_name.begin(), resource_name.end(),
                                 [&](auto &kv) { return kv.second == name; });
          it != resource_name.end()) {
        allocation_data[it->first] = n;
        need_data[it->first] -= n;
      } else {
        std::cout << "该资源不存在\n";
      }
    }
    std::vector<bool> finish(pro_num, false);
    std::vector<std::string> safe_sequence;
    if (!IsSafe(finish, safe_sequence)) {
      std::cout << "该操作使系统不安全, 取消操作\n";
      max_data = std::move(original_max);
      need_data = std::move(original_need);
      allocation_data = std::move(original_allocation);
    }
  }

  void Caculate() {
    // 计算need数组
    for (auto &[name, vec] : need) {
      for (int i = 0; i < resource_num; i++) {
        vec[i] = max[name][i] - allocation[name][i];
      }
    }
    // 计算avaliable数组
    for (int i = 0; i < resource_num; i++) {
      for (auto &[_, vec] : allocation) {
        avaliable[i] -= vec[i];
      }
    }
  }

  void PrintData() {
    std::cout << "    Max  Alloc Need  Avaliable\n";
    std::cout << "   ";
    for (int j = 0; j < 4; j++) {
      for (int i = 0; i < resource_num; i++) {
        std::cout << resource_name[i] << ' ';
      }
    }
    std::cout << '\n';
    for (auto &[name, vec] : max) {
      std::cout << name << ' ';
      for (int i = 0; i < resource_num; i++) {
        std::cout << vec[i] << ' ';
      }
      for (int i = 0; i < resource_num; i++) {
        std::cout << allocation[name][i] << ' ';
      }
      for (int i = 0; i < resource_num; i++) {
        std::cout << need[name][i] << ' ';
      }
      for (int i = 0; i < resource_num; i++) {
        std::cout << avaliable[i] << ' ';
      }
      std::cout << '\n';
    }
  }

  void GetSafeSequence() {
    std::vector<bool> finish(pro_num, false);
    std::vector<std::string> safe_sequence;
    if (IsSafe(finish, safe_sequence)) {
      std::cout << "安全序列: " << safe_sequence[0];
      for (int i = 1; i < safe_sequence.size(); i++) {
        std::cout << std::format(" -> {}", safe_sequence[i]);
      }
      std::cout << '\n';
    } else {
      std::cout << "没有安全序列\n";
    }
  }
};

int main() {
  BankerAlgorithm ba;
  while (true) {
    std::cout << "选择操作: \n[1] 初始化数据\n[2] 检查安全性\n[3] "
                 "更新已分配资源\n[4] 打印当前所有数据\n[5] 退出\n";
    int choice;
    std::cin >> choice;
    switch (choice) {
    case 1:
      ba.InitAllData();
      ba.Caculate();
      ba.PrintData();
    case 2:
      ba.GetSafeSequence();
      break;
    case 3:
      ba.UpdateResourceForProcess();
      break;
    case 4:
      ba.PrintData();
      break;
    case 5:
      exit(0);
    default:
      std::cout << "看起来你输错选项了\n";
    }
  }
}