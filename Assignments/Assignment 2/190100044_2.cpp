#include <iostream>
#include <string>
#include <vector>

#define ull unsigned long long int

using namespace std;

// Fibonacci Word
// f(a) = "ab"
// f(b) = "a"
class Fibo {
public:
  int set_size = 2;
  vector<ull> lengths;
  string f_a = "ab", f_b = "a";

  Fibo() {
    cout << "Fibo found\n";
    return;
  }

  void zeroth(ull n) {
    cout << "0//" << n << "\n";
    return;
  }
  void first(ull n) {
    cout << "1//" << n << "\n";
    return;
  }
  void second(string s) {
    cout << "2//" << s << "\n";
    return;
  }
  void third(string s) {
    cout << "3//" << s << "\n";
    return;
  }
  void run() {
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
};

// Thue-Morse Word
// f(a) = "ab"
// f(b) = "ba"
class TM {
public:
  int set_size = 2;
  vector<ull> lengths;
  string f_a = "ab", f_b = "ba";

  TM() {
    cout << "TM found\n";
    return;
  }

  void zeroth(ull n) {
    cout << "0//" << n << "\n";
    return;
  }
  void first(ull n) {
    cout << "1//" << n << "\n";
    return;
  }
  void second(string s) {
    cout << "2//" << s << "\n";
    return;
  }
  void third(string s) {
    cout << "3//" << s << "\n";
    return;
  }
  void run() {
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
};

// Exponential Word
// Each f(x) had at least 2 characters
// Length grows at least O(2^n)
class Expo {
public:
  int set_size;
  vector<ull> lengths;
  string *fs;

  Expo(int set_size_, string fs_[]) {
    set_size = set_size_;
    fs = new string[set_size];
    for (int i = 0; i < set_size; i++) {
      fs[i] = fs_[i];
    }
    cout << "Expo found\n";
    return;
  }

  void zeroth(ull n) {
    cout << "0//" << n << "\n";
    return;
  }
  void first(ull n) {
    cout << "1//" << n << "\n";
    return;
  }
  void second(string s) {
    cout << "2//" << s << "\n";
    return;
  }
  void third(string s) {
    cout << "3//" << s << "\n";
    return;
  }
  void run() {
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
};

// Linear Word
// Bit of a weirdo
class Linear {
public:
  int set_size;
  string *fs;

  Linear(int set_size_, string fs_[]) {
    set_size = set_size_;
    fs = new string[set_size];
    for (int i = 0; i < set_size; i++) {
      fs[i] = fs_[i];
    }
    cout << "Linear found\n";
    return;
  }

  void zeroth(ull n) {
    cout << "0//" << n << "\n";
    return;
  }
  void first(ull n) {
    cout << "1//" << n << "\n";
    return;
  }
  void second(string s) {
    cout << "2//" << s << "\n";
    return;
  }
  void third(string s) {
    cout << "3//" << s << "\n";
    return;
  }
  void run() {
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
};

int main() {
  int set_size;
  cin >> set_size >> ws;

  string fs[set_size];
  for (int i = 0; i < set_size; i++) {
    getline(cin, fs[i]);
    cout << fs[i] << "\n";
  }
  // cout << endl;

  string morph_type;
  if (set_size == 2 && fs[0] == "ab" && fs[1] == "a") {
    Fibo morphism;
    morphism.run();
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
