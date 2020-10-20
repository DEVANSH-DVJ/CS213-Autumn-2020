#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main() {
  int n = 10;
  // int parent[n] = {-1, 0, 1, 2, 2, 4, 4, 0, 7, 7}; // 3 5 6 4 2 1 8 9 7 0
  // int parent[n] = {-1, 0, 1, 2, 3, 3, 1, 6, 0, 8}; // 4 5 3 2 7 6 1 9 8 0
  int parent[n] = {-1, 0, 1, 1, 3, 1, 0, 6, 6, 0}; // 2 4 3 5 1 7 8 6 9 0

  vector<bool> visited(n, false);
  list<int> L({0});
  visited[0] = true;
  for (int i = n - 1; i > 0; i--) {
    list<int>::iterator p = L.begin();
    int j = i;
    while (j > -1 && !visited[j]) {
      visited[j] = true;
      L.insert(p, j);
      j = parent[j];
    }
  }

  for (auto i : L) {
    cout << i << " ";
  }
  cout << "\n";

  return 0;
}
