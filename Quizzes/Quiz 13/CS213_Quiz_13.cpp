#include <iostream>
#include <list>

using namespace std;

#define li list<int>

// void fun(list<int> &l) {
//   auto p = l.begin();
//   for (int i = 0; i < l.size() / 2; i++) {
//     l.insert(l.end(), *(++p));
//     p = l.erase(p);
//     // cout << *p << endl;
//     // cout << *p << "\\";
//   }
//   // cout << endl;
// }
void fun(list<int> &l) {
  auto p = l.begin();
  for (int i = 0; i < l.size() / 2; i++) {
    l.insert(l.end(), *++p);
    p = l.erase(p);
  }
}

void invfun(list<int> &l) {
  auto p = l.begin();
  auto q = p;

  for (int i = 0; i < (1 + l.size()) / 2; i++)
    q++;
  for (int i = 0; i < l.size() / 2; i++) {
    l.insert(++p, *q);
    q = l.erase(q);
  }
}

int main() {
  uint n = 11;
  li l(n);
  int j = 0;
  for (auto &i : l) {
    i = j;
    j = j + 2;
  }

  for (auto &i : l) {
    cout << i << " ";
  }
  cout << endl;

  fun(l);

  for (auto &i : l) {
    cout << i << " ";
  }
  cout << endl;

  invfun(l);

  for (auto &i : l) {
    cout << i << " ";
  }
  cout << endl;

  return 0;
}
