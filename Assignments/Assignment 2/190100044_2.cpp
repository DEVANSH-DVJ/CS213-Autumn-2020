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
  vector<ull> lengths;
  string *fs;

  Expo(int set_size_, string fs_[]);

  void zeroth(ull n);
  void first(ull n);
  void second(string s);
  void third(string s);
  void run();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////// Declaration: Linear Word ///////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Linear Word
// Bit of a weirdo
class Linear {
public:
  int set_size;
  string *fs;

  Linear(int set_size_, string fs_[]);

  void zeroth(ull n);
  void first(ull n);
  void second(string s);
  void third(string s);
  void run();
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
  cout << lengths[n] << endl;
  return;
}
void Fibo::first(ull n) {
  // cout << "1//" << n << "\n";
  cout << at_index(n) << endl;
  return;
}
void Fibo::second(string s) {
  // cout << "2//" << s << "\n";
  substring(s);
  return;
}
void Fibo::third(string s) {
  cout << "3//" << s << "\n";
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
      cout << endl;
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

  // cout << lengths[lengths.size() - 1] << endl;
  // cout << i << endl;

  lengths[0] = 1;
  lengths[1] = 2;
  for (int i = 2; i < 87; i++) {
    lengths[i] = lengths[i - 1] + lengths[i - 2];
  }
  // cout << lengths[86] << endl;

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
  for (; i < 61; i++) {
    if (lengths[i] > n) {
      break;
    }
  }
  string txt = generate(i + 2);
  // cout << i << endl;
  ull index = KMPSearch(pat, txt);
  // cout << txt.size() << endl;
  // cout << index << endl;
  if (index == txt.size()) {
    cout << -1 << endl;
  } else {
    cout << index << endl;
  }
  return;
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
  cout << lengths[n] << endl;
  return;
}
void TM::first(ull n) {
  // Count the number of ones in bit rep of n
  // (http://www.ams.org/publicoutreach/feature-column/fc-2013-09)
  // cout << "1//" << n << "\n";
  cout << at_index(n) << endl;
  return;
}
void TM::second(string s) {
  // cout << "2//" << s << "\n";
  substring(s);
  return;
}
void TM::third(string s) {
  cout << "3//" << s << "\n";
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
      cout << endl;
    }
  }
}
void TM::assign_length() {
  ull x = 1;
  for (int i = 0; i < 61; i++) {
    lengths[i] = x;
    x *= 2;
  }
  // cout << lengths[60] << endl;

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
  for (; i < 61; i++) {
    if (lengths[i] > n) {
      break;
    }
  }
  string txt = generate(i + 2);
  // cout << i << endl;
  ull index = KMPSearch(pat, txt);
  // cout << txt.size() << endl;
  // cout << index << endl;
  if (index == txt.size()) {
    cout << -1 << endl;
  } else {
    cout << index << endl;
  }
  return;
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
  cout << "Expo found\n";
  return;
}

void Expo::zeroth(ull n) {
  cout << "0//" << n << "\n";
  return;
}
void Expo::first(ull n) {
  cout << "1//" << n << "\n";
  return;
}
void Expo::second(string s) {
  cout << "2//" << s << "\n";
  return;
}
void Expo::third(string s) {
  cout << "3//" << s << "\n";
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
      cout << endl;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////// Definition: Linear Word /////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Linear Word
// Bit of a weirdo
Linear::Linear(int set_size_, string fs_[]) {
  set_size = set_size_;
  fs = new string[set_size];
  for (int i = 0; i < set_size; i++) {
    fs[i] = fs_[i];
  }
  cout << "Linear found\n";
  return;
}

void Linear::zeroth(ull n) {
  cout << "0//" << n << "\n";
  return;
}
void Linear::first(ull n) {
  cout << "1//" << n << "\n";
  return;
}
void Linear::second(string s) {
  cout << "2//" << s << "\n";
  return;
}
void Linear::third(string s) {
  cout << "3//" << s << "\n";
  return;
}
void Linear::run() {
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
      cout << endl;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
  int set_size;
  cin >> set_size >> ws;

  string fs[set_size];
  for (int i = 0; i < set_size; i++) {
    getline(cin, fs[i]);
    // cout << fs[i] << "\n";
  }
  // cout << endl;

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
      Linear morphism(set_size, fs);
      morphism.run();
    }
  }

  return 0;
}
