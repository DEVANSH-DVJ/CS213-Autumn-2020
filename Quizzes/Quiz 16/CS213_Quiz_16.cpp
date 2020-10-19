#include <iostream>

using namespace std;

int *num_trees(int n) {
  int *T = new int[n + 1];
  T[0] = 1;
  for (int i = 0; i < n; i++) {
    T[i + 1] = 0;
    for (int j = 0; j < (i + 1) / 2; j++) {
      T[i + 1] += T[j] * T[i - j];
    }
    if (!(i % 2)) {
      T[i + 1] += T[i / 2] * (T[i / 2] + 1) / 2;
    }
  }
  return T;
}

int main() {
  int n = 10;
  int *T = num_trees(n);
  for (int i = 0; i <= n; i++) {
    cout << i << ": " << T[i] << "\n";
  }

  return 0;
}
