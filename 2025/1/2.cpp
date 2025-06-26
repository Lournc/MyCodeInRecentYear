#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

struct Edge {
  int u, v, w;
  bool operator<(const Edge &other) const {
    return w > other.w; // Sort in descending order
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int n, m, q;
    cin >> n >> m >> q;
    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
      cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    sort(edges.begin(), edges.end());

    vector<vector<vector<pair<int, int>>>> events(
        n + 1, vector<vector<pair<int, int>>>(n + 1));
    vector<vector<int>> adj(n + 1);
    vector<vector<int>> dist(
        n + 1, vector<int>(n + 1, -INF)); // Track maximum path length

    for (int a = 1; a <= n; ++a) {
      for (int b = 1; b <= n; ++b) {
        if (a == b) {
          dist[a][b] = 0;
          events[a][b].emplace_back(0, 0); // Initial state with 0 edges
        } else {
          dist[a][b] = -INF;
        }
      }
    }

    for (const Edge &e : edges) {
      int u = e.u, v = e.v, w = e.w;
      adj[u].push_back(v);
      adj[v].push_back(u);

      vector<vector<int>> new_dist(n + 1, vector<int>(n + 1, -INF));
      for (int a = 1; a <= n; ++a) {
        queue<int> q;
        new_dist[a][a] = 0;
        q.push(a);

        while (!q.empty()) {
          int node = q.front();
          q.pop();
          for (int neighbor : adj[node]) {
            if (new_dist[a][neighbor] < new_dist[a][node] + 1) {
              new_dist[a][neighbor] = new_dist[a][node] + 1;
              q.push(neighbor);
            }
          }
        }
      }

      for (int a = 1; a <= n; ++a) {
        for (int b = 1; b <= n; ++b) {
          if (new_dist[a][b] > dist[a][b]) {
            dist[a][b] = new_dist[a][b];
            events[a][b].emplace_back(w, dist[a][b]);
          }
        }
      }
    }

    // Prepare events for binary search by reversing to ascending order of
    // weights
    for (int a = 1; a <= n; ++a) {
      for (int b = 1; b <= n; ++b) {
        reverse(events[a][b].begin(), events[a][b].end());
      }
    }

    while (q--) {
      int a, b, k;
      cin >> a >> b >> k;
      auto &ev = events[a][b];
      int left = 0, right = ev.size() - 1;
      int ans = -1;
      while (left <= right) {
        int mid = (left + right) / 2;
        if (ev[mid].second >= k) {
          ans = ev[mid].first;
          right = mid - 1;
        } else {
          left = mid + 1;
        }
      }
      cout << ans << '\n';
    }
  }

  return 0;
}