#include <iostream>

using namespace std;

int f_1(int T[], int n);
int f_2(int T[], int n);
int g_1(int T[], int n);
int g_2(int T[], int n);

int f_1(int T[], int n) {
  if (n == 0) {
    return 0;
  }

  int min = T[0];
  int index = 0;
  for (int i = 1; i < n; i++) {
    if (T[i] < min) {
      index = i;
      min = T[i];
    }
  }

  int T_l[index];
  int T_r[n - index - 1];

  for (int i = 0; i < index; i++) {
    T_l[i] = T[i];
  }
  for (int i = index + 1; i < n; i++) {
    T_r[i - index - 1] = T[i];
  }

  return g_1(T_l, index) + g_2(T_r, n - index - 1);
}

int f_2(int T[], int n) {
  if (n == 0) {
    return 1;
  }

  int min = T[0];
  int index = 0;
  for (int i = 1; i < n; i++) {
    if (T[i] < min) {
      index = i;
      min = T[i];
    }
  }

  int T_l[index];
  int T_r[n - index - 1];

  for (int i = 0; i < index; i++) {
    T_l[i] = T[i];
  }
  for (int i = index + 1; i < n; i++) {
    T_r[i - index - 1] = T[i];
  }

  return g_1(T_l, index) + 1;
}

int g_1(int T[], int n) {
  if (n == 0) {
    return 0;
  }

  int max = T[n - 1];
  int index = n - 1;
  for (int i = n - 2; i > -1; i--) {
    if (T[i] > max) {
      index = i;
      max = T[i];
    }
  }

  int T_l[index];
  int T_r[n - index - 1];

  for (int i = 0; i < index; i++) {
    T_l[i] = T[i];
  }
  for (int i = index + 1; i < n; i++) {
    T_r[i - index - 1] = T[i];
  }

  return f_2(T_l, index) + f_1(T_r, n - index - 1);
}

int g_2(int T[], int n) {
  if (n == 0) {
    return 1;
  }

  int max = T[n - 1];
  int index = n - 1;
  for (int i = n - 2; i > -1; i--) {
    if (T[i] > max) {
      index = i;
      max = T[i];
    }
  }

  int T_l[index];
  int T_r[n - index - 1];

  for (int i = 0; i < index; i++) {
    T_l[i] = T[i];
  }
  for (int i = index + 1; i < n; i++) {
    T_r[i - index - 1] = T[i];
  }

  return 1 + f_1(T_r, n - index - 1);
}

int main() {
  int n;
  cin >> n;
  int T[n];
  for (int i = 0; i < n; i++) {
    cin >> T[i];
  }

  cout << f_1(T, n) << endl;

  return 0;
}
