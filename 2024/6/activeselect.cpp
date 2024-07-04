#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<pair<int, int>> activity_selection(vector<pair<int, int>> &activities) {
  sort(activities.begin(), activities.end(),
       [](const pair<int, int> &a, const pair<int, int> &b) {
         return a.second < b.second;
       });

  vector<pair<int, int>> selected_activities;

  selected_activities.push_back(activities[0]);
  int last_finish_time = activities[0].second;

  for (int i = 1; i < activities.size(); i++) {
    if (activities[i].first >= last_finish_time) {
      selected_activities.push_back(activities[i]);
      last_finish_time = activities[i].second;
    }
  }

  return selected_activities;
}
                 
int main() {
  vector<pair<int, int>> activities = {{1, 3}, {2, 5}, {4, 6},
                                       {6, 8}, {5, 9}, {8, 9}};
  vector<pair<int, int>> result = activity_selection(activities);

  cout << "选择的活动：" << endl;
  for (const auto &activity : result) {
    cout << "活动(" << activity.first << ", " << activity.second << ")" << endl;
  }

  return 0;
}