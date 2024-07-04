#include <climits>
#include <iostream>
#include <vector>

using namespace std;

const int INF = INT_MAX;

void tsp_backtracking(const vector<vector<int>> &graph, vector<bool> &visited,
                      int currPos, int n, int count, int cost, int &minCost,
                      vector<int> &path, vector<int> &bestPath) {
  if (count == n && graph[currPos][0]) {
    if (cost + graph[currPos][0] < minCost) {
      minCost = cost + graph[currPos][0];
      bestPath = path;
      bestPath.push_back(0);
    }
    return;
  }

  for (int i = 0; i < n; i++) {
    if (!visited[i] && graph[currPos][i]) {
      visited[i] = true;
      path.push_back(i);
      tsp_backtracking(graph, visited, i, n, count + 1,
                       cost + graph[currPos][i], minCost, path, bestPath);
      path.pop_back();
      visited[i] = false;
    }
  }
}

int main() {
  vector<vector<int>> graph = {
      {0, 10, 15, 20}, {10, 0, 35, 25}, {15, 35, 0, 30}, {20, 25, 30, 0}};

  int n = graph.size();
  vector<bool> visited(n, false);
  visited[0] = true;

  int minCost = INF;
  vector<int> path = {0};
  vector<int> bestPath;

  tsp_backtracking(graph, visited, 0, n, 1, 0, minCost, path, bestPath);

  cout << "使用回溯法求解TSP的最小成本是: " << minCost << endl;
  cout << "最优路径是: ";
  for (int i : bestPath) {
    cout << i << " ";
  }
  cout << endl;

  return 0;
}
