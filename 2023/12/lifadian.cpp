#include <format>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

enum class HairCase { HairCut = 1, Hair_Dye = 2, Hair_Perm = 3 };
int hair_cut{10};
int hair_dye{15};
int hair_perm{20};
class Patron {
  std::string name;
  int sex;                     // 性别0女1男
  std::string contact_details; // 联系方式
  int visits_number{};

public:
  Patron() = delete;
  explicit Patron(std::string name, int sex, std::string contact_details,
                  int visits_number)
      : name(std::move(name)), sex(sex),
        contact_details(std::move(contact_details)),
        visits_number(visits_number) {}
  std::string GetName() { return name; }
  [[nodiscard]] int GetSex() const { return sex; }
  std::string GetContact() { return contact_details; }
  [[nodiscard]] int GetVisits() const { return visits_number; }
  void IncreaseVisit() { visits_number++; }
};

class PatronManage : public Patron {
public:
  double GetPrice(HairCase choice);
};

double PatronManage::GetPrice(HairCase choice) {
  int cost;
  int visits_number = GetVisits();
  switch (choice) {
  case HairCase::HairCut:
    cost = hair_cut;
    break;
  case HairCase::Hair_Dye:
    cost = hair_dye;
    break;
  case HairCase::Hair_Perm:
    cost = hair_perm;
    break;
  default:
    std::cout << "本店没有这种服务\n";
    return 0;
  }
  return std::max(cost / double((50 + visits_number) / 50), cost * 0.7);
}

class PatronQ {
public:
  explicit PatronQ(PatronManage *data) { data_.reset(data); }
  std::shared_ptr<PatronManage> data_{nullptr};
  std::shared_ptr<PatronQ> next_{nullptr};
};

class WaitQueue {
  std::shared_ptr<PatronQ> front_{nullptr};
  std::shared_ptr<PatronQ> end_{nullptr};
  unsigned int size_{};

public:
  PatronQ *front() { return front_.get(); }
  PatronQ *end() { return end_.get(); }
  void pop() {
    if (front_ == nullptr) {
      return;
    }
    front_ = front_->next_;
    size_--;
  }
  void emplace(std::string &name, int &sex, std::string &contact_details,
               int &visits_number) {
    PatronManage *manage = reinterpret_cast<PatronManage *>(
        new Patron(name, sex, contact_details, visits_number));
    std::shared_ptr<PatronQ> new_end = std::make_shared<PatronQ>(manage);
    if (front_ == nullptr) {
      front_ = new_end;
    }
    if (end_ != nullptr) {
      end_->next_ = std::move(new_end);
    }
    end_ = new_end;
    size_++;
  }
  void reduce() {
    size_--;
    if (size_ == 0) {
      front_ = end_ = nullptr;
    }
  }
  [[nodiscard]] unsigned int size() const { return size_; }
};

class WaitQueueManage {
  WaitQueue data_;

public:
  WaitQueue GetData() { return data_; }
  PatronManage GetNext() { return *data_.front()->data_; }
  void LeaveFront() { data_.pop(); }
  void AddPatron(std::string name, int sex, std::string contact,
                 int visit_number) {
    data_.emplace(name, sex, contact, visit_number);
  }
  unsigned int GetSize() { return data_.size(); }
  void Leave(const std::string &contact) {
    auto patron = data_.front();
    if (patron == nullptr) {
      std::cout << "没有人在等待...\n";
      return;
    }
    auto data = reinterpret_cast<Patron *>(patron->data_.get());
    if (contact == data->GetContact()) {
      data_.pop();
      return;
    }
    while (patron) {
      if (patron->next_ != nullptr &&
          patron->next_->data_->GetContact() == contact) {
        patron->next_ = patron->next_->next_;
        data_.reduce();
        return;
      }
      patron = patron->next_.get();
    }
    std::cout << "查无此人\n";
  }
  int HowMany(const std::string &contact) {
    int ans{};
    auto patron = data_.front();
    if (patron == nullptr) {
      std::cout << "没有人在等待...\n";
      return -1;
    }
    while (patron) {
      if (patron->data_->GetContact() == contact) {
        return ans;
      }
      ans++;
      patron = patron->next_.get();
    }
    std::cout << "查无此人...\n";
    return -1;
  }
};
// 文件流
std::fstream file;
// 以联系方式为key，此哈希表保存所有数据
std::unordered_map<std::string, Patron> user_data;
// 等待队列
WaitQueueManage wait_manage;
void InitializationSystem() {
  file.open("user_data.txt");
  if (!file.is_open()) {
    file.clear();
    file.open("user_data.txt", std::ios::out); // 创建文件
    file.close();
    file.open("user_data.txt");
  }
  std::string name;
  int sex;
  std::string contact;
  int visits;
  while (file >> name >> sex >> contact >> visits) {
    user_data.insert({contact, Patron{name, sex, contact, visits}});
  }
  file.close();
  std::cout << "数据加载完毕...\n";
}
void AddNewConstant() {
  std::string name;
  int sex;
  std::string contact;
  std::cout << "输入顾客的姓名、性别（0代表女性，1代表男性）、联系方式\n";
  std::cin >> name >> sex >> contact;
  if (user_data.find(name) != user_data.end()) {
    std::cout << "该顾客是老顾客，不能添加\n";
    return;
  }
  user_data.insert({contact, Patron{name, sex, contact, 0}});
  user_data.at(contact).IncreaseVisit();
  std::cout << "已添加\n";
}
void SearchPatron() {
  std::string contact;
  std::cout << "输入顾客的联系方式，以查询\n";
  std::cin >> contact;
  auto user = user_data.find(contact);
  if (user != user_data.end()) {
    std::cout << std::format(
        "已查到顾客信息：\n姓名： {} 性别：{} 联系方式：{} 光顾次数：{}\n",
        user->second.GetName(), user->second.GetSex() ? "男" : "女",
        user->second.GetContact(), user->second.GetVisits());
    return;
  }
  std::cout << "看起来这个顾客不在系统中...\n";
}
void ChangeInfo() {
  std::cout << "请输入用户以前的联系方式以及新的联系方式\n";
  std::string old_contact, new_contact;
  std::cin >> old_contact >> new_contact;
  auto user = user_data.find(old_contact);
  if (user != user_data.end()) {
    user_data.insert(
        {new_contact, Patron{user->second.GetName(), user->second.GetSex(),
                             new_contact, user->second.GetVisits()}});
    user_data.erase(user->first);
    return;
  }
  std::cout << "看起来用户不在系统中...\n";
}
void ShowInfo() {
  std::cout << "所有顾客信息：\n";
  for (auto &[_, user] : user_data) {
    std::cout << std::format("姓名： {} 性别：{} 联系方式：{} 光顾次数：{}\n",
                             user.GetName(), user.GetSex() ? "男" : "女",
                             user.GetContact(), user.GetVisits());
  }
}
void CalculateCost() {
  std::string contact;
  std::cout << "输入用户联系方式，查询消费金额\n";
  std::cin >> contact;
  if (user_data.find(contact) != user_data.end()) {
    auto user =
        reinterpret_cast<PatronManage *>(&user_data.find(contact)->second);
    std::cout << std::format(
        "该顾客剪发需要：{}元，染发需要：{}元，烫发需要：{}元\n",
        user->GetPrice(HairCase::HairCut), user->GetPrice(HairCase::Hair_Dye),
        user->GetPrice(HairCase::Hair_Perm));
    return;
  }
  std::cout << "查无此人...\n";
}
void SaveData() {
  file.open("user_data.txt",
            std::ios_base::in | std::ios_base::out | std::ios_base::trunc);
  for (auto &[_, user] : user_data) {
    file << user.GetName() << ' ' << user.GetSex() << ' ' << user.GetContact()
         << ' ' << user.GetVisits() << std::endl;
  }
  file.close();
  std::cout << "所有用户信息保存完毕\n";
}
void QueueSearch() {
  std::string contact;
  std::cout << "输入你想查询的顾客的联系方式：";
  std::cin >> contact;
  if (int num = wait_manage.HowMany(contact); num > -1) {
    std::cout << "该顾客前边还有" << num << "个人在等待\n";
  }
}
void WaitPatron() {
  std::cout << "输入要等待的顾客的联系方式：";
  std::string contract;
  std::cin >> contract;
  auto user = user_data.find(contract);
  if (user != user_data.end()) {
    user->second.IncreaseVisit();
    wait_manage.AddPatron(user->second.GetName(), user->second.GetSex(),
                          user->second.GetContact(), user->second.GetVisits());
    std::cout << "已将该顾客加入等待队列了\n";
    return;
  }
  std::cout << "看起来该顾客还没在系统中，先添加顾客信息吧\n";
}
void WaitLeave() {
  std::cout << "输入在等待队列中离开的顾客联系方式：";
  std::string contract;
  std::cin >> contract;
  wait_manage.Leave(contract);
  std::cout << "操作完成\n";
}
void WaitTotal() {
  std::cout << std::format("共有 {} 个人在等待...\n", wait_manage.GetSize());
}
void WaitShow() {
  if (wait_manage.GetSize() == 0) {
    std::cout << "没人在等待\n";
    return;
  }
  auto data = wait_manage.GetData();
  std::cout << std::format("下一个顾客是：{}，后边的顾客有：",
                           wait_manage.GetNext().GetName());
  data.pop();
  while (data.size()) {
    std::cout << data.front()->data_->GetName() << std::endl;
    data.pop();
  }
}
void ManageUi();
int main() {
  InitializationSystem();
  while (true) {
    ManageUi();
    int choice;
    std::cin >> choice;
    switch (choice) {
    case 1:
      AddNewConstant();
      break;
    case 2:
      SearchPatron();
      break;
    case 3:
      ChangeInfo();
      break;
    case 4:
      ShowInfo();
      break;
    case 5:
      CalculateCost();
      break;
    case 6:
      SaveData();
      break;
    case 7:
      QueueSearch();
      break;
    case 8:
      WaitPatron();
      break;
    case 9:
      WaitLeave();
      break;
    case 10:
      WaitTotal();
      break;
    case 11:
      WaitShow();
      break;
    case 12:
      SaveData();
      return 0;
    default:
      continue;
    }
  }
}

void ManageUi() {
  using std::cout;
  cout << "欢迎使用形象设计理发店管理系统\n"
       << "一.顾客信息管理\n"
       << "1.添加新顾客       2.查询顾客信息\n"
       << "3.修改顾客信息     4.显示顾客信息\n"
       << "5.计算消费金额     6.保存顾客信息\n"
       << "二.顾客等待队列管理\n"
       << "7.查询             8.等待\n"
       << "9.离开             10.统计\n"
       << "11.显示            12.退出系统\n"
       << "请输入相应编号:";
}