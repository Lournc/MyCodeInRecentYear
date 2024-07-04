#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// 边结构定义
struct edge {
  int u, v, weight;
  bool operator<(const edge &other) const { return weight < other.weight; }
};

// 不相交集合
class union_find {
public:
  union_find(int n) : parent(n), rank(n, 0) {
    for (int i = 0; i < n; ++i)
      parent[i] = i;
  }

  int find(int u) {
    if (u != parent[u])
      parent[u] = find(parent[u]);
    return parent[u];
  }

  void union_sets(int u, int v) {
    int root_u = find(u);
    int root_v = find(v);
    if (root_u != root_v) {
      if (rank[root_u] > rank[root_v])
        parent[root_v] = root_u;
      else if (rank[root_u] < rank[root_v])
        parent[root_u] = root_v;
      else {
        parent[root_v] = root_u;
        rank[root_u]++;
      }
    }
  }

private:
  vector<int> parent;
  vector<int> rank;
};

int kruskal_mst(int n, vector<edge> &edges) {
  sort(edges.begin(), edges.end()); // 按照边的权重排序

  union_find uf(n);
  int mst_weight = 0;

  for (const edge &e : edges) {
    int u = e.u;
    int v = e.v;
    if (uf.find(u) != uf.find(v)) {
      mst_weight += e.weight;
      uf.union_sets(u, v);
    }
  }

  return mst_weight;
}

int main() {
  int n;
  cin >> n;
  vector<edge> edges;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int weight;
      cin >> weight;
      if (i < j && weight != 0) {
        edges.push_back({i, j, weight});
      }
    }
  }

  int result = kruskal_mst(n, edges);
  cout << result << endl;

  return 0;
}
