#include <iostream>

template <typename T> bool majority(T a[], int n) {
  T x = a[0];
  int cnt = 1;
  for (int i = 1; i < n; i++) {
    if (x == a[i])
      cnt++;
    else if (cnt == 0) {
      x = a[i];
      cnt = 1;
    } else
      cnt--;
  }
  std::cout << x << ";;;\n";
  cnt = 0;
  for (int i = 0; i < n; i++)
    if (x == a[i])
      cnt++;
  return (cnt > n / 2);
}

int main() {
  int x[18]{2, 1, 2, 2, 3, 7, 1, 1, 3, 3, 7, 1, 1, 1, 1, 1, 1, 2};

  std::cout << majority(x, 18) << std::endl;

  return 0;
}
