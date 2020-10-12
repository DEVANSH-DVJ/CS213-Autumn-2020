#include <iostream>
#include <stack>

using namespace std;

int height(string s) {
  stack<int> h;
  int curr = 0, ht = 0;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == '(') {
      if (++curr > ht)
        ht++;
      h.push(curr);
    } else {
      curr = h.top();
      h.pop();
    }
    // cout << s[i] << "\tht: " << ht << "\tcurr: " << curr << endl;
  }
  return ht;
}

int func(string s) {
  int cnt = 0, num = 0;
  for (int i = 0; i < s.length(); i++)
    if (s[i] == '(')
      cnt++;
    else {
      cnt--;
      if (cnt == 0)
        num++;
    }
  return num;
}

int main() {
  string s = "((((())))()(()()))";
  string s1 = "()(())((()()))";
  cout << height(s) << endl;
  cout << func(s) << endl;
  cout << height(s1) << endl;
  cout << func(s1) << endl;
  return 0;
}
