#include <iostream>

const int n = 10;
int a[n]{0, 9, 8, 7, 6, 5, 4, 3, 2, 1}, f[n];
int count=0;
bool check(int j, int i) {
  count++;
  // std::cout << i << "//" << j << std::endl;
  return a[j] >= a[i];
}

int main() {

  f[0] = -1;

  for (int i = 1; i < n; i++) {
    int j = i - 1;
    while ((j >= 0) && (check(j, i)))
      j = f[j];
    f[i] = j;
  }

  for (int i = 0; i < n; i++) {
    std::cout << f[i] << " ";
  }
  std::cout << std::endl;

  std::cout << count << std::endl;

  return 0;
}
