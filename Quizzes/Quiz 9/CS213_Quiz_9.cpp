#include <iostream>

int count = 0;

int longest_presuf(int *a, int n) {
  int len[n];
  len[0] = 0;
  for (int i = 1; i < n; i++) {
    int j = len[i - 1];
    std::cout << i << j << "//" << count++ << "\n";
    while ((j != 0) && (a[j] != a[i])) {
      j = 0;
      std::cout << i << j << "//" << count++ << "\n";
    }
    std::cout << i << j << "//" << count++ << "\n";
    if (a[j] == a[i])
      len[i] = j + 1;
    else
      len[i] = 0;
  }
  return len[n - 1];
}

int main() {
  int x[20]{1, 2, 3, 1, 2, 3, 1, 1, 3};
  // int x[20]{1, 2, 1, 1, 2};

  std::cout << longest_presuf(x, 2) << std::endl;
  count = 0;
  std::cout << longest_presuf(x, 3) << std::endl;
  count = 0;
  std::cout << longest_presuf(x, 4) << std::endl;
  count = 0;
  std::cout << longest_presuf(x, 5) << std::endl;
  count = 0;
  std::cout << longest_presuf(x, 6) << std::endl;
  count = 0;
  std::cout << longest_presuf(x, 7) << std::endl;
  count = 0;
  std::cout << longest_presuf(x, 8) << std::endl;
  count = 0;
  std::cout << longest_presuf(x, 9) << std::endl;
  count = 0;

  return 0;
}
