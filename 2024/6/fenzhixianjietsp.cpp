#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int INF = INT_MAX;

struct Node {
  vector<int> path;
  int reducedCost;
  int vertex;
  int level;

  bool operator>(const Node &other) const {
    return reducedCost > other.reducedCost;
  }
};

int calculateCost(vector<vector<int>> matrix) {
  int cost = 0;

  for (int i = 0; i < matrix.size(); i++) {
    int rowMin = *min_element(matrix[i].begin(), matrix[i].end());
    if (rowMin != INF) {
      cost += rowMin;
      for (int j = 0; j < matrix[i].size(); j++) {
        if (matrix[i][j] != INF) {
          matrix[i][j] -= rowMin;
        }
      }
    }
  }

  for (int j = 0; j < matrix[0].size(); j++) {
    int colMin = INF;
    for (int i = 0; i < matrix.size(); i++) {
      if (matrix[i][j] < colMin) {
        colMin = matrix[i][j];
      }
    }
    if (colMin != INF) {
      cost += colMin;
      for (int i = 0; i < matrix.size(); i++) {
        if (matrix[i][j] != INF) {
          matrix[i][j] -= colMin;
        }
      }
    }
  }

  return cost;
}

void tsp_branch_and_bound(const vector<vector<int>> &graph) {
  priority_queue<Node, vector<Node>, greater<Node>> pq;
  int n = graph.size();
  vector<int> initialPath = {0};

  Node root = {initialPath, calculateCost(graph), 0, 0};
  pq.push(root);

  int minCost = INF;
  vector<int> minPath;

  while (!pq.empty()) {
    Node node = pq.top();
    pq.pop();

    if (node.level == n - 1) {
      int totalCost = node.reducedCost + graph[node.vertex][0];

      if (totalCost < minCost) {
        minCost = totalCost;
        minPath = node.path;
        minPath.push_back(0);
      }
      continue;
    }

    for (int i = 0; i < n; i++) {
      if (find(node.path.begin(), node.path.end(), i) == node.path.end() &&
          graph[node.vertex][i] != INF) {
        Node child;
        child.path = node.path;
        child.path.push_back(i);
        child.level = node.level + 1;
        child.vertex = i;

        vector<vector<int>> tempMatrix = graph;
        for (int j = 0; j < n; j++) {
          tempMatrix[node.vertex][j] = INF;
          tempMatrix[j][i] = INF;
        }
        tempMatrix[i][0] = INF;

        child.reducedCost = node.reducedCost + graph[node.vertex][i] +
                            calculateCost(tempMatrix);
        pq.push(child);
      }
    }
  }

  cout << "使用分支限界法求解TSP的最小成本是: " << minCost << endl;
  cout << "最优路径是: ";
  for (int i : minPath) {
    cout << i << " ";
  }
  cout << endl;
}

int main() {
  vector<vector<int>> graph = {
      {0, 10, 15, 20}, {10, 0, 35, 25}, {15, 35, 0, 30}, {20, 25, 30, 0}};

  tsp_branch_and_bound(graph);

  return 0;
}
