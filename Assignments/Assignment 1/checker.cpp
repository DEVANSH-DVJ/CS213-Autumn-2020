#include "190100044_1.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  srand(time(NULL));
  int n = 100;
  int s[100];
  for (int i = 0; i < 100; i++)
    s[i] = i;
  int corr = 0;
  //   for (int i = 0; i < 1000; i++) {
  //     random_shuffle(s, s + 100);
  //     permutation p(100, s);
  //     int last = -1;
  //     bool b = true;
  //     for (int j = 0; j < 100; j++) {
  //       permutation q = p ^ j;
  //       int t = q.log(p);
  //       if (t != last + 1 && t != 0)
  //         b = false;
  //     }
  //     if (b)
  //       corr++;
  //   }
  for (int i = 0; i < n; i++) {
    random_shuffle(s, s + 100);
    permutation p(100, s);
    random_shuffle(s, s + 100);
    permutation q(100, s);
    int t = q.log(p);
    if (t != -1) {
      permutation r = p ^ t;
      if (q == r)
        corr++;
    }
    else {
      corr++;
    }
  }
  cout << "CORRECT: " << corr << '\n';
  cout << "WRONG: " << n - corr << '\n';
  return 0;
}
