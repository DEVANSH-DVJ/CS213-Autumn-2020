#include <iostream>
#include <vector>

using namespace std;

#define vi vector<int>

int main() {
  uint n = 10;
  vi v(n);
  for (uint i = 0; i < v.size(); i++) {
    v[i] = i;
  }
  v[2]=1;

  // int i = 0;
  // while (i < v.size()) {
  //   if (v[i] % 2 == 1) {
  //     v.erase(v.begin() + i);
  //   } else {
  //     i++;
  //   }
  // }

  // int j = 0;
  // for (int i = 0; i < v.size(); i++) {
  //   if (v[i] % 2 == 0)
  //     v[j++] = v[i];
  // }
  // v.erase(v.begin() + j, v.end());

  // int i = 4;
  // v.erase(v.begin(),
  //         v.insert(v.end(), v.begin(), v.begin() + i) + i - v.size());

  int i = 0, l = 6;
  v.assign(v.begin() + i, v.begin() + i + l);

  for (uint i = 0; i < v.size(); i++) {
    cout << v[i] << " ";
  }
  cout << endl;

  return 0;
}
