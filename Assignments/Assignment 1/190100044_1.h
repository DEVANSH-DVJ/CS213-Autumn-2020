#include <bits/stdc++.h>
// #include <iostream>

class permutation {
private:
  int len, *arr; // Length of array, Array of integers

public:
  permutation(int n, int a[]);
  ~permutation();
  permutation(permutation const &q);
  permutation const operator=(permutation const &q);

  int size() const;
  int *to_array() const;

  permutation const operator-() const;
  permutation const operator*(permutation const &q) const;
  permutation const square_root() const;
  permutation const operator^(long long int i) const;
  bool is_power(permutation const &q) const;
  int log(permutation const &q) const;

  // Helper class functions
  bool operator==(permutation const &q) const; // Equality operator
  bool is_identity() const; // Is Identity permutation?
  permutation make_identity() const; // Returns an identity permutation
  int order() const; // Order of the permutation i.e. p^(?) = Identity
};

permutation::permutation(int n, int a[]) {
  len = n;
  arr = new int[len];
  for (int i = 0; i < len; i++) {
    arr[i] = a[i];
  }
}

permutation::~permutation() { delete arr; }

permutation::permutation(permutation const &q) {
  len = q.size();
  arr = new int[len];
  int *a = q.to_array();
  for (int i = 0; i < len; i++) {
    arr[i] = a[i];
  }
}

permutation const permutation::operator=(permutation const &q) {
  len = q.size();
  arr = new int[len];
  int *a = q.to_array();
  for (int i = 0; i < len; i++) {
    arr[i] = a[i];
  }

  return *this;
}

int permutation::size() const { return len; }

int *permutation::to_array() const { return arr; }

permutation const permutation::operator-() const {
  int a[len];
  for (int i = 0; i < len; i++) {
    a[i] = arr[len - i - 1];
  }
  return permutation(len, a);
}

permutation const permutation::operator*(permutation const &q) const {
  int ma[len];
  int *a = q.to_array();
  for (int i = 0; i < len; i++) {
    ma[i] = arr[a[i]];
  }
  return permutation(len, ma);
}

permutation const permutation::square_root() const {
  // Sorry, the variable names are bad...
  int i, j, k, l, n;

  n = len;
  int b[10000], c[10000], d[10000], e[10000], g[10000], h[10000];
  for (i = 1; i <= n; i++) {
    g[i] = arr[i - 1] + 1;
  }

  for (i = 1; i <= n; i++) {
    if (!b[i]) {
      for (j = i, k = 0; !b[j]; j = g[j], k++)
        b[j] = 1;
      c[i] = k, d[k]++;
    }
  }

  for (i = 1; i <= n; i++) {
    if ((!(i & 1)) && (d[i] & 1)) {
      return make_identity();
    }
  }

  for (i = 1; i <= n; i++) {
    if (c[i] & 1) {
      for (j = i, k = 1; k < (c[i] + 1) / 2; j = g[j], k++)
        ;
      for (l = i, k = 1; k <= c[i]; j = g[j], l = g[l], k++)
        h[j] = l;
    } else if (!e[c[i]])
      e[c[i]] = i;
    else {
      for (j = e[c[i]], l = i, k = 1; k <= c[i]; j = g[j], l = g[l], k++)
        h[j] = l, h[l] = g[j];
      e[c[i]] = 0;
    }
  }

  int hh[n];
  for (i = 1; i <= n; i++) {
    hh[i - 1] = h[i] - 1;
  }

  return permutation(n, hh);
}

// permutation const permutation::operator^(long long int i) const {
//   permutation q(*this);
//   for (int j = 1; j < i; j++) {
//     q = q * (*this);
//   }
//   return q;
// }

// permutation const permutation::operator^(long long int i) const {
//   permutation q(*this);
//   long long int j = 1;
//   for (; j < i; j++) {
//     q = q * (*this);
//     if (q.is_identity())
//       break;
//   }

//   if (i == j)
//     return q;

//   long long int rem = i % j;
//   for (j = 0; j < rem; j++) {
//     q = q * (*this);
//   }
//   return q;
// }

permutation const permutation::operator^(long long int i) const {
  permutation q = make_identity();
  if (i == 0) {
    return q;
  } else if (i == 1) {
    return *this;
  } else if (i == 2) {
    return *this * *this;
  }

  permutation mul(*this);
  long long int j = i;
  while (j) {
    if (j % 2) {
      q = q * mul;
    }
    j = j / 2;
    mul = mul * mul;
  }
  return q;
}

bool permutation::is_power(permutation const &q) const {
  if (log(q) == -1)
    return false;
  else
    return true;
}

int permutation::log(permutation const &q) const {
  if (this->is_identity())
    return 0;
  if (q == *this)
    return 1;
  permutation r = q;
  int ord = order();
  for (int j = 1; j < ord; j++) {
    r = r * (q);
    if (r == *this)
      return j + 1;
  }
  return -1;
}

bool permutation::operator==(permutation const &q) const {
  if (len != q.size())
    return false;
  int *a = q.to_array();
  for (int i = 0; i < len; i++) {
    if (arr[i] != a[i])
      return false;
  }
  return true;
}

bool permutation::is_identity() const {
  for (int i = 0; i < len; i++) {
    if (arr[i] != i)
      return false;
  }
  return true;
}

permutation permutation::make_identity() const {
  int a[len];
  for (int i = 0; i < len; i++) {
    a[i] = i;
  }
  return permutation(len, a);
}

int permutation::order() const {
  int n = len;
  std::vector<int> v;
  int visit[n] = {0}, c = 0;
  for (int i = 0; i < n; i++) {
    if (visit[i])
      continue;
    c = 1;
    int curr = arr[i];
    while (curr != i) {
      c++;
      curr = arr[curr];
    }
    v.push_back(c);
  }
  int ans = 1;
  for (auto x : v)
    ans = ans / std::__gcd(ans, x) * x;
  return ans;
}
