#include <iostream>

const int n = 7;
int a[n], f[n];

int count;

bool check(int j, int i) {
  count++;
  // std::cout << i << "//" << j << std::endl;
  return a[j] >= a[i];
}

int main() {

  for (long long int l = 0; l < 6543210; l++) {
    count = 0;
    long long int k = l;
    for (int j = 0; j < n; j++) {
      a[j] = (k % 10);
      k /= 10;
    }
    f[0] = -1;

    for (int i = 1; i < n; i++) {
      int j = i - 1;
      while ((j >= 0) && (check(j, i)))
        j = f[j];
      f[i] = j;
    }

    if (count == 2 * n - 3) {
      bool x = true;
      for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
          if (a[j] == a[i])
            x = false;
        }
      }
      if (x)
        break;
    }
  }

  for (int i = 0; i < n; i++) {
    std::cout << f[i] << " ";
  }
  std::cout << std::endl;

  for (int i = 0; i < n; i++) {
    std::cout << a[i] << " ";
  }
  std::cout << std::endl;

  return 0;
}
