#include <iostream>
#include <string>
#include <vector>

#define ull unsigned long long int

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fills lps[] for given pattern pat[0,...,M-1]
void computeLPSArray(string pat, ull M, ull *lps) {
  // length of the previous longest prefix suffix
  ull len = 0;

  lps[0] = 0; // lps[0] is always 0

  // the loop calculates lps[i] for i = 1 to M-1
  ull i = 1;
  while (i < M) {
    if (pat[i] == pat[len]) {
      len++;
      lps[i] = len;
      i++;
    } else // (pat[i] != pat[len])
    {
      // This is tricky. Consider the example.
      // AAACAAAA and i = 7. The idea is similar
      // to search step.
      if (len != 0) {
        len = lps[len - 1];

        // Also, note that we do not increment
        // i here
      } else // if (len == 0)
      {
        lps[i] = 0;
        i++;
      }
    }
  }
}

// Prints occurrences of txt[] in pat[]
ull KMPSearch(string pat, string txt) {
  ull M = pat.size();
  ull N = txt.size();

  // create lps[] that will hold the longest prefix suffix
  // values for pattern
  ull lps[M];

  // Preprocess the pattern (calculate lps[] array)
  computeLPSArray(pat, M, lps);

  ull i = 0; // index for txt[]
  ull j = 0; // index for pat[]
  while (i < N) {
    if (pat[j] == txt[i]) {
      j++;
      i++;
    }

    if (j == M) {
      return i - j;
    }

    // mismatch after j matches
    else if (i < N && pat[j] != txt[i]) {
      // Do not match lps[0..lps[j-1]] characters,
      // they will match anyway
      if (j != 0)
        j = lps[j - 1];
      else
        i = i + 1;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////// Declaration: Fibonacci Word /////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fibonacci Word
// f(a) = "ab"
// f(b) = "a"
class Fibo {
public:
  int set_size = 2;
  // vector<ull> lengths;
  ull lengths[87]; // 86th term is above the limit.
  string f_a = "ab", f_b = "a";

  Fibo();

  void zeroth(ull n);
  void first(ull n);
  void second(string s);
  void third(string s);
  void run();

  void assign_length();
  char at_index(ull i);
  string generate(int n);
  void substring(string pat);
  void subsequence(string pat);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////// Declaration: Thue-Morse Word ///////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Thue-Morse Word
// f(a) = "ab"
// f(b) = "ba"
class TM {
public:
  int set_size = 2;
  // vector<ull> lengths;
  ull lengths[61]; // 60th term is above the limit.
  string f_a = "ab", f_b = "ba";

  TM();

  void zeroth(ull n);
  void first(ull n);
  void second(string s);
  void third(string s);
  void run();

  void assign_length();
  char at_index(ull i);
  string generate(int n);
  void substring(string pat);
  void subsequence(string pat);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////// Declaration: Exponential Word ///////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Exponential Word
// Each f(x) had at least 2 characters
// Length grows at least O(2^n)
class Expo {
public:
  int set_size;
  vector<vector<ull>> lengths;
  string *fs;
  int **matrix;

  Expo(int set_size_, string fs_[]);

  void zeroth(ull n);
  void first(ull n);
  void second(string s);
  void third(string s);
  void run();
  void init_matrix();
  ull *multiply_mat_vec(ull *vec);
  vector<ull> assign_length(int c);
  char at_index(ull n, int a, int power);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////// Declaration: Poly Word ////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Poly Word
// Bit of a weirdo
class Poly {
public:
  int set_size;
  string *fs;
  ull **matrix;

  Poly(int set_size_, string fs_[]);

  void zeroth(ull n);
  void first(ull n);
  void second(string s);
  void third(string s);
  void run();
  void init_matrix();
  ull **multiply_matrix(ull **mat1, ull **mat2);
  ull *multiply_mat_vec(ull **mat, ull *vec);
  ull **identity_matrix();
  ull assign_length(ull n);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////// Definition: Fibonacci Word //////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fibonacci Word
// f(a) = "ab"
// f(b) = "a"
Fibo::Fibo() {
  // cout << "Fibo found\n";
  assign_length();
  return;
}

void Fibo::zeroth(ull n) {
  // cout << "0//" << n << "\n";
  cout << lengths[n] << "\n";
  return;
}
void Fibo::first(ull n) {
  // cout << "1//" << n << "\n";
  cout << at_index(n) << "\n";
  return;
}
void Fibo::second(string s) {
  // cout << "2//" << s << "\n";
  substring(s); // Fix this
  return;
}
void Fibo::third(string s) {
  // cout << "3//" << s << "\n";
  subsequence(s);
  return;
}
void Fibo::run() {
  int ops;
  cin >> ops;
  int choice;
  ull n;
  string s;
  for (int i = 0; i < ops; i++) {
    cin >> choice;
    if (choice == 0) {
      cin >> n;
      zeroth(n);
    } else if (choice == 1) {
      cin >> n;
      first(n);
    } else if (choice == 2) {
      cin >> ws;
      getline(cin, s);
      second(s);
    } else if (choice == 3) {
      cin >> ws;
      getline(cin, s);
      third(s);
    } else {
      cout << "\n";
    }
  }
}
void Fibo::assign_length() {
  // lengths.push_back(1);
  // lengths.push_back(2);
  // lengths.push_back(3);

  // ull f;
  // int i = 2;
  // while (f < 1000000000000000000) {
  //   f = lengths[i] + lengths[i - 1];
  //   lengths.push_back(f);
  //   i++;
  // }

  // cout << lengths[lengths.size() - 1] << "\n";
  // cout << i << "\n";

  lengths[0] = 1;
  lengths[1] = 2;
  for (int i = 2; i < 87; i++) {
    lengths[i] = lengths[i - 1] + lengths[i - 2];
  }
  // cout << lengths[86] << "\n";

  return;
}
char Fibo::at_index(ull n) {
  int i = 0;
  for (; i < 87; i++) {
    if (lengths[i] > n) {
      break;
    }
  }
  if (lengths[i] - 1 == n) {
    if (i % 2) {
      return 'b';
    } else {
      return 'a';
    }
  }

  return at_index(n - lengths[i - 1]);
}
string Fibo::generate(int n) {
  if (n == 0) {
    return "a";
  } else if (n == 1) {
    return "ab";
  } else {
    return generate(n - 1) + generate(n - 2);
  }
}
void Fibo::substring(string pat) {
  int i = 0;
  ull n = pat.size();
  for (; i < 87; i++) {
    if (lengths[i] >= n) {
      break;
    }
  }
  string txt = generate(i + 4);
  ull index = KMPSearch(pat, txt);
  ull last = index + n - 1;
  for (int j = i; j < i + 5; j++) {
    if (lengths[j] > last) {
      cout << j << " " << index << "\n";
      return;
    }
  }
  cout << -1 << "\n";
  return;
}
void Fibo::subsequence(string pat) {
  int i = 0;
  string::iterator pat_it = pat.begin();
  ull n = 3 * pat.size();
  for (; i < 87; i++) {
    if (lengths[i] >= n) {
      break;
    }
  }
  string txt = generate(i);
  string::iterator txt_it = txt.begin();

  while (true) {
    if (pat_it == pat.end()) {
      ull index = txt_it - txt.begin();
      for (int i = 0; i < 87; i++) {
        if (lengths[i] >= index) {
          cout << i << " " << index << "\n";
          return;
        }
      }
    }
    if (txt_it == txt.end()) {
      cout << -1 << "\n";
      return;
    }
    if (*pat_it == *txt_it) {
      pat_it++;
      txt_it++;
    } else {
      txt_it++;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////// Definition: Thue-Morse Word /////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Thue-Morse Word
// f(a) = "ab"
// f(b) = "ba"
TM::TM() {
  // cout << "TM found\n";
  assign_length();
  return;
}

void TM::zeroth(ull n) {
  // cout << "0//" << n << "\n";
  cout << lengths[n] << "\n";
  return;
}
void TM::first(ull n) {
  // Count the number of ones in bit rep of n
  // (http://www.ams.org/publicoutreach/feature-column/fc-2013-09)
  // cout << "1//" << n << "\n";
  cout << at_index(n) << "\n";
  return;
}
void TM::second(string s) {
  // cout << "2//" << s << "\n";
  substring(s); // Fix this
  return;
}
void TM::third(string s) {
  // cout << "3//" << s << "\n";
  subsequence(s);
  return;
}
void TM::run() {
  int ops;
  cin >> ops;
  int choice;
  ull n;
  string s;
  for (int i = 0; i < ops; i++) {
    cin >> choice;
    if (choice == 0) {
      cin >> n;
      zeroth(n);
    } else if (choice == 1) {
      cin >> n;
      first(n);
    } else if (choice == 2) {
      cin >> ws;
      getline(cin, s);
      second(s);
    } else if (choice == 3) {
      cin >> ws;
      getline(cin, s);
      third(s);
    } else {
      cout << "\n";
    }
  }
}
void TM::assign_length() {
  ull x = 1;
  for (int i = 0; i < 61; i++) {
    lengths[i] = x;
    x *= 2;
  }
  // cout << lengths[60] << "\n";

  return;
}
char TM::at_index(ull n) {
  // Alternative using recursion
  // https://cs.uwaterloo.ca/~shallit/Talks/green3.pdf
  int set_count = 0;

  while (n != 0) {
    if (n % 2)
      set_count++;
    n /= 2;
  }

  if (set_count % 2)
    return 'b';
  else
    return 'a';
}
string TM::generate(int n) {
  if (n == 0) {
    return "a";
  } else if (n == 1) {
    return "ab";
  } else if (n == 2) {
    return "abba";
  } else {
    string s = generate(n - 1);
    ull ss = s.size();
    for (int i = 0; i < ss; i++) {
      if (s[i] == 'a')
        s += 'b';
      else
        s += 'a';
    }
    return s;
  }
}
void TM::substring(string pat) {
  int i = 0;
  ull n = pat.size();
  for (; i < 87; i++) {
    if (lengths[i] >= n) {
      break;
    }
  }
  string txt = generate(i + 4);
  ull index = KMPSearch(pat, txt);
  ull last = index + n - 1;
  for (int j = i; j < i + 5; j++) {
    if (lengths[j] > last) {
      cout << j << " " << index << "\n";
      return;
    }
  }
  cout << -1 << "\n";
  return;
}
void TM::subsequence(string pat) {
  int i = 0;
  string::iterator pat_it = pat.begin();
  ull n = 3 * pat.size();
  for (; i < 61; i++) {
    if (lengths[i] >= n) {
      break;
    }
  }
  string txt = generate(i);
  string::iterator txt_it = txt.begin();

  while (true) {
    if (pat_it == pat.end()) {
      ull index = txt_it - txt.begin();
      for (int i = 0; i < 61; i++) {
        if (lengths[i] >= index) {
          cout << i << " " << index << "\n";
          return;
        }
      }
    }
    if (txt_it == txt.end()) {
      cout << -1 << "\n";
      return;
    }
    if (*pat_it == *txt_it) {
      pat_it++;
      txt_it++;
    } else {
      txt_it++;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////// Definition: Exponential Word ////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Exponential Word
// Each f(x) had at least 2 characters
// Length grows at least O(2^n)
Expo::Expo(int set_size_, string fs_[]) {
  set_size = set_size_;
  fs = new string[set_size];
  for (int i = 0; i < set_size; i++) {
    fs[i] = fs_[i];
  }
  // cout << "Expo found\n";
  // for (int i = 0; i < set_size; i++) {
  //   cout << i << ": " << fs[i] << "\n";
  // }

  init_matrix();
  for (int i = 0; i < set_size; i++) {
    lengths.push_back(assign_length(i));
  }
  return;
}

void Expo::zeroth(ull n) {
  // cout << "0//" << n << "\n";
  cout << lengths[0][n] << "\n";
  return;
}
void Expo::first(ull n) {
  // cout << "1//" << n << "\n";
  int power = 0;
  for (; power < lengths[0].size(); power++) {
    if (lengths[0][power] > n) {
      break;
    }
  }
  cout << at_index(n, 0, power) << "\n";

  return;
}
void Expo::second(string s) {
  // cout << "2//" << s << "\n";
  cout << "\n";
  return;
}
void Expo::third(string s) {
  // cout << "3//" << s << "\n";
  cout << "\n";
  return;
}
void Expo::run() {
  int ops;
  cin >> ops;
  int choice;
  ull n;
  string s;
  for (int i = 0; i < ops; i++) {
    cin >> choice;
    if (choice == 0) {
      cin >> n;
      zeroth(n);
    } else if (choice == 1) {
      cin >> n;
      first(n);
    } else if (choice == 2) {
      cin >> ws;
      getline(cin, s);
      second(s);
    } else if (choice == 3) {
      cin >> ws;
      getline(cin, s);
      third(s);
    } else {
      cout << "\n";
    }
  }
}
void Expo::init_matrix() {
  matrix = new int *[set_size];
  for (int i = 0; i < set_size; ++i) {
    matrix[i] = new int[set_size];
  }

  for (int i = 0; i < set_size; i++) {
    for (int j = 0; j < set_size; j++) {
      matrix[i][j] = 0;
    }
  }
  for (int i = 0; i < set_size; i++) {
    int len = fs[i].length();
    for (int j = 0; j < len; j++) {
      matrix[int(fs[i][j]) - 97][i]++;
    }
  }

  // for (int i = 0; i < set_size; i++) {
  //   for (int j = 0; j < set_size; j++) {
  //     cout << matrix[i][j] << " ";
  //   }
  //   cout << "\n";
  // }
}
ull *Expo::multiply_mat_vec(ull *vec) {
  ull *res;
  res = new ull[set_size];
  for (int i = 0; i < set_size; i++) {
    res[i] = 0;
    for (int j = 0; j < set_size; j++) {
      res[i] += matrix[i][j] * vec[j];
    }
  }
  return res;
}
vector<ull> Expo::assign_length(int c) {
  vector<ull> res;
  ull len = 0;
  res.push_back(1);
  ull *vec = new ull[set_size];
  for (int i = 0; i < set_size; i++) {
    vec[i] = matrix[i][c];
    len += vec[i];
  }
  res.push_back(len);
  int count = 0;
  while (count < 61) {
    if (len > 1000000000000000000) {
      break;
    }
    len = 0;
    vec = multiply_mat_vec(vec);
    for (int i = 0; i < set_size; i++) {
      len += vec[i];
    }
    // cout << len << "\n";
    res.push_back(len);
    count++;
  }
  return res;
}
char Expo::at_index(ull n, int a, int power) {
  // cout << n << ";;" << a << ";;" << power << "\n";
  if (power == 0) {
    return char(a + 97);
  }

  for (int j = 0; j < fs[a].size(); j++) {
    char c = fs[a][j];
    int ci = int(c) - 97;
    // cout << c << "//\n";
    if (n < lengths[ci][power - 1]) {
      return at_index(n, ci, power - 1);
    } else {
      n -= lengths[ci][power - 1];
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////// Definition: Poly Word /////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Poly Word
// Bit of a weirdo
Poly::Poly(int set_size_, string fs_[]) {
  set_size = set_size_;
  fs = new string[set_size];
  for (int i = 0; i < set_size; i++) {
    fs[i] = fs_[i];
  }
  // cout << "Poly found\n";
  // for (int i = 0; i < set_size; i++) {
  //   cout << i << ": " << fs[i] << "\n";
  // }

  init_matrix();
  return;
}

void Poly::zeroth(ull n) {
  // cout << "0//" << n << "\n";
  if (n == 0) {
    cout << 1 << "\n";
  }
  cout << assign_length(n - 1) << "\n";
  return;
}
void Poly::first(ull n) {
  // cout << "1//" << n << "\n";
  cout << "\n";
  return;
}
void Poly::second(string s) {
  // cout << "2//" << s << "\n";
  cout << "\n";
  return;
}
void Poly::third(string s) {
  // cout << "3//" << s << "\n";
  cout << "\n";
  return;
}
void Poly::run() {
  int ops;
  cin >> ops;
  int choice;
  ull n;
  string s;
  for (int i = 0; i < ops; i++) {
    cin >> choice;
    if (choice == 0) {
      cin >> n;
      zeroth(n);
    } else if (choice == 1) {
      cin >> n;
      first(n);
    } else if (choice == 2) {
      cin >> ws;
      getline(cin, s);
      second(s);
    } else if (choice == 3) {
      cin >> ws;
      getline(cin, s);
      third(s);
    } else {
      cout << "\n";
    }
  }
}
void Poly::init_matrix() {
  matrix = new ull *[set_size];
  for (int i = 0; i < set_size; ++i) {
    matrix[i] = new ull[set_size];
  }

  for (int i = 0; i < set_size; i++) {
    for (int j = 0; j < set_size; j++) {
      matrix[i][j] = 0;
    }
  }
  for (int i = 0; i < set_size; i++) {
    int len = fs[i].length();
    for (int j = 0; j < len; j++) {
      matrix[int(fs[i][j]) - 97][i]++;
    }
  }

  // for (int i = 0; i < set_size; i++) {
  //   for (int j = 0; j < set_size; j++) {
  //     cout << matrix[i][j] << " ";
  //   }
  //   cout << "\n";
  // }
}
ull **Poly::multiply_matrix(ull **mat1, ull **mat2) {
  ull **res;
  res = new ull *[set_size];
  for (int i = 0; i < set_size; ++i) {
    res[i] = new ull[set_size];
  }
  int i, j, k;
  for (i = 0; i < set_size; i++) {
    for (j = 0; j < set_size; j++) {
      res[i][j] = 0;
      for (k = 0; k < set_size; k++)
        res[i][j] += mat1[i][k] * mat2[k][j];
    }
  }
  return res;
}
ull *Poly::multiply_mat_vec(ull **mat, ull *vec) {
  ull *res;
  res = new ull[set_size];
  for (int i = 0; i < set_size; i++) {
    res[i] = 0;
    for (int j = 0; j < set_size; j++) {
      res[i] += mat[i][j] * vec[j];
    }
  }
  return res;
}
ull **Poly::identity_matrix() {
  ull **id;
  id = new ull *[set_size];
  for (int i = 0; i < set_size; ++i) {
    id[i] = new ull[set_size];
  }

  for (int i = 0; i < set_size; i++) {
    for (int j = 0; j < set_size; j++) {
      id[i][j] = 0;
    }
    id[i][i] = 1;
  }
  return id;
}
ull Poly::assign_length(ull n) {
  ull **mat = matrix;
  ull **res = identity_matrix();
  // cout << n;
  while (n > 0) {
    if (n % 2) {
      res = multiply_matrix(res, mat);
    }
    n /= 2;
    mat = multiply_matrix(mat, mat);
  }
  ull *vec = new ull[set_size];
  for (int i = 0; i < set_size; i++) {
    vec[i] = matrix[i][0];
  }
  ull *fin = multiply_mat_vec(res, vec);
  ull len = 0;
  for (int i = 0; i < set_size; i++) {
    len += fin[i];
  }
  return len;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int set_size;
  cin >> set_size >> ws;

  string fs[set_size];
  for (int i = 0; i < set_size; i++) {
    getline(cin, fs[i]);
    // cout << fs[i] << "\n";
  }
  // cout << "\n";

  string morph_type;
  if (set_size == 2 && fs[0] == "ab" && fs[1] == "a") {
    Fibo morphism;
    morphism.run();
    // cout << morphism.generate(15);
  } else if (set_size == 2 && fs[0] == "ab" && fs[1] == "ba") {
    TM morphism;
    morphism.run();
  } else {
    bool is_2_expo = true;
    for (int i = 0; i < set_size; i++) {
      if (fs[i].size() < 2)
        is_2_expo = false;
    }
    if (is_2_expo) {
      Expo morphism(set_size, fs);
      morphism.run();
    } else {
      Poly morphism(set_size, fs);
      morphism.run();
    }
  }

  return 0;
}
