#include "190100044_1.h"
#include <iostream>

#include <cstdio>

// int b[1200000], c[1200000], d[1200000], e[1200000], g[1200000], h[1200000];
// int i, j, k, l, n;

// permutation sq_root(permutation perm) {
//   n = perm.size();
//   int *a = perm.to_array();
//   for (i = 1; i <= n; i++) {
//     g[i] = a[i - 1] + 1;
//   }

//   for (i = 1; i <= n; i++) {
//     if (!b[i]) {
//       for (j = i, k = 0; !b[j]; j = g[j], k++)
//         b[j] = 1;
//       c[i] = k, d[k]++;
//     }
//   }

//   for (i = 1; i <= n; i++) {
//     if ((!(i & 1)) && (d[i] & 1)) {
//       return perm.make_identity();
//     }
//   }

//   for (i = 1; i <= n; i++) {
//     if (c[i] & 1) {
//       for (j = i, k = 1; k < (c[i] + 1) / 2; j = g[j], k++)
//         ;
//       for (l = i, k = 1; k <= c[i]; j = g[j], l = g[l], k++)
//         h[j] = l;
//     } else if (!e[c[i]])
//       e[c[i]] = i;
//     else {
//       for (j = e[c[i]], l = i, k = 1; k <= c[i]; j = g[j], l = g[l], k++)
//         h[j] = l, h[l] = g[j];
//       e[c[i]] = 0;
//     }
//   }

//   int hh[n];
//   for (i = 1; i <= n; i++) {
//     hh[i - 1] = h[i] - 1;
//   }

//   return permutation(n, hh);
// }

// #include <bits/stdc++.h>
// using namespace std;

// permutation sq_root(permutation perm) {
//   int cur = 0, n, i, j;
//   n = perm.size();
//   int s[n], ret[n], *a, b[n];
//   a = perm.to_array();
//   for (i = 1; i <= n; ++i) {
//     if (b[a[i]])
//       continue;
//     cur = 0;
//     for (j = a[i]; !b[a[j]]; j = a[j])
//       ++cur, b[a[j]] = 1;
//     if (cur & 1) {
//       int x = a[i], u = a[i];
//       for (j = 0; j < (cur) / 2; ++j)
//         x = a[x];
//       ret[i] = x;
//       for (j = 0; j < cur - 1; ++j) {
//         ret[u] = a[x];
//         x = a[x];
//         u = a[u];
//       }
//     } else {
//       int t = s[cur];
//       if (t == 0) {
//         s[cur] = i;
//         continue;
//       }
//       s[cur] = 0;
//       int u = i;
//       for (j = 0; j < cur; ++j) {
//         ret[t] = u, ret[u] = a[t];
//         t = a[t], u = a[u];
//       }
//     }
//   }
//   for (i = 0; i <= n; i += 2)
//     if (s[i]) {
//       return perm.make_identity();
//     }
//   return permutation(n, ret);
// }

int main() {
  int array1[20] = {1,  4,  2,  3,  0,  5,  6,  9,  7,  8,
                    10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
  int array2[5] = {1, 2, 3, 4, 0};
  int array3[20] = {4,  0,  3,  2,  1,  5,  6,  8,  9,  7,
                    10, 12, 11, 13, 14, 16, 15, 19, 18, 17};
  int array4[20] = {4,  0,  2,  3,  1,  5,  6,  8,  9,  7,
                    10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
  int array5[20] = {1,  2,  3,  4,  5,  6,  7,  8,  9,  0,
                    11, 13, 14, 15, 17, 16, 12, 18, 10, 19};
  int array6[20] = {6, 10, 11, 7,  3,  12, 1, 5,  18, 0,
                    4, 19, 8,  15, 14, 17, 9, 16, 2,  13};
  int array7[20] = {1, 4,  19, 5,  7,  8,  10, 12, 2,  6,
                    3, 13, 18, 17, 14, 16, 0,  9,  11, 15};

  int n, *arr;
  permutation const p(20, array7);
  // permutation p(5, array2);

  // permutation r = -p;

  permutation r = p.make_identity();
  for (int i = 0; i < 2500000; i++)
    r = p.square_root();

  // permutation r = p * p * p * p * p;
  // r = r * r * r * r * r;
  // permutation r2 = p ^ 25;

  // permutation r(20, array6);

  n = r.size();
  arr = r.to_array();
  std::cout << n << "\n";

  for (int i = 0; i < n; i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;

  // n = r2.size();
  // arr = r2.to_array();
  // std::cout << n << "\n";

  // for (int i = 0; i < n; i++) {
  //   std::cout << arr[i] << " ";
  // }
  // std::cout << std::endl;

  std::cout << r.log(p) << std::endl;
  std::cout << r.order() << std::endl;
  std::cout << p.order() << std::endl;
  std::cout << r.is_power(p) << std::endl;

  // int array1[5] = {0, 2, 4, 1, 3};
  // int array2[5] = {0, 2, 4, 3, 1};
  // permutation const p(5, array1);
  // permutation q(5, array2);
  // permutation r = q = p;

  // int n = r.size();
  // int *arr = r.to_array();
  // std::cout << n << "\n";

  // for (int i = 0; i < n; i++) {
  //   std::cout << arr[i] << " ";
  // }
  // std::cout << std::endl;

  return 0;
}
