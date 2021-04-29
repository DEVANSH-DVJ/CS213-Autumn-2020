#include <iostream>
#include <list>

using namespace std;

int timer;

class Graph {
  int n;
  list<int> *adj;
  int *dfs_start, *dfs_end;
  // int parent;

public:
  Graph(int n) {
    this->n = n;
    adj = new list<int>[n];
    dfs_start = new int[n];
    dfs_end = new int[n];
    for (int i = 0; i < n; i++) {
      dfs_start[i] = dfs_end[i] = -1;
    }
  }

  void add(int x, int y) { adj[x].push_back(y); }

  void dfs(int u, int parent) {
    dfs_start[u] = ++timer;
    for (auto v : adj[u]) {
      if (dfs_start[v] == -1) {
        dfs(v, u);
      } else {
        if (parent == v) {
          cout << u << " and " << v << endl;
        }
      }
    }
    dfs_end[u] = ++timer;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;
  cin >> n >> m;

  Graph g(n);
  int x, y;
  for (int i = 0; i < m; ++i) {
    cin >> x >> y;
    g.add(x, y);
  }

  timer = 0;

  g.dfs(0, -1);

  return 0;
}
