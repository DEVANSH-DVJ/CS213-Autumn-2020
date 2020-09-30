#include "190100044_1.h"
#include <bits/stdc++.h>
#include <chrono>
using namespace std;
typedef long long ll;
#define pb push_back
const ll INF = 1e18;


int main() {
  srand(time(0));
  int n;
  cin >> n;
  int aray[n];
  for (ll i = 0; i < n; i++)
    aray[i] = i;
  int t;
  cin >> t;
  int c = 0, high = 0, same = 0;
  int total = 0;
  while (t--) {
    ll raise = rand() % (INF);
    random_shuffle(aray, aray + n);
    permutation p = permutation(n, aray);
    int lcm = p.order();
    auto start = std::chrono::high_resolution_clock::now();
    permutation q = p ^ raise;
    int val = q.log(p);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    total += duration.count();
    if (val == raise)
      same++;
    if (val >= lcm) {
      c++;
      continue;
    }
    high = max(high, val);
    if (val == -1) {
      c++;
      continue;
    }
    permutation ans = p ^ val;
    int *arr = q.to_array(), *a = ans.to_array();
    for (int i = 0; i < n; i++) {
      if (a[i] != arr[i]) {
        c++;
        break;
      }
    }
  }
  cout << "Highest value of log: " << high << "\n";
  cout << "Number of times the raised power equals log: " << same << "\n";
  cout << "Number of wrong answers: " << c << "\n";
  cout << "Execution time (in microseconds): " << total << "\n";
  return 0;
}
