// #include <cstdio>

// int b[1200000], c[1200000], d[1200000], e[1200000], g[1200000], h[1200000];
// int i, j, k, l, n;

// int main() {
//   scanf("%d", &n);
//   for (i = 1; i <= n; i++)
//     scanf("%d", &g[i]);

//   for (i = 1; i <= n; i++)
//     printf("%d", g[i]);
//   printf("\n");

//   for (i = 1; i <= n; i++)
//     if (!b[i]) {
//       for (j = i, k = 0; !b[j]; j = g[j], k++)
//         b[j] = 1;
//       c[i] = k, d[k]++;
//     }
//   for (i = 1; i <= n; i++)
//     if ((!(i & 1)) && (d[i] & 1)) {
//       printf("-1");
//       return 0;
//     }
//   for (i = 1; i <= n; i++)
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
//   for (i = 1; i <= n; i++)
//     printf("%d ", h[i]);
//   return 0;
// }

// #include <bits/stdc++.h>
// using namespace std;
// const int N = 1e6 + 5;
// int s[N], ret[N], a[N], b[N];
// int main() {
//   int cur = 0, n, i, j;
//   scanf("%d", &n);
//   for (i = 1; i <= n; ++i)
//     scanf("%d", &a[i]);
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
//       printf("-1\n");
//       return 0;
//     }
//   for (i = 1; i <= n; ++i)
//     printf("%d ", ret[i]);
//   cout << endl;
// }

#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int p[1000003], n, a[1000003], q[1000003], father[1000003], cnt;
bool vis[1000003];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &p[i]);
  for (int i = 1; i <= n; i++)
    if (!vis[i]) {
      int len = 0;
      for (int k = i; !vis[k]; vis[k] = true, len++, k = p[k])
        ;
      if (len & 1) {
        cnt += len;
        for (int k = 0, t = 0, v = i; t < len; t++, k = (k + 2) % len, v = p[v])
          a[k] = v;
        for (int k = 0; k < len; k++)
          q[a[k]] = a[(k + 1) % len];
      } else {
        if (father[len] == 0) {
          father[len] = i;
          continue;
        }
        cnt += 2 * len;
        int u = father[len];
        father[len] = 0;
        for (int k = 0, t = 0, v = i; t < len; k += 2, t++, v = p[v])
          a[k] = v;
        for (int k = 1, t = 0, v = u; t < len; k += 2, t++, v = p[v])
          a[k] = v;
        for (int k = 0; k < 2 * len; k++)
          q[a[k]] = a[(k + 1) % (2 * len)];
      }
    }
  if (cnt < n)
    cout << -1 << endl;
  else
    for (int i = 1; i <= n; i++)
      printf("%d ", q[i]);
  return 0;
}
