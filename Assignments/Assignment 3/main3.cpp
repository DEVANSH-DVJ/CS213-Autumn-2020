#include "190100044_3.h"

using namespace std;

int main() {
  quad_tree qt1(2);
  qt1.set(0, 2, 1, 3, 1);
  qt1.print();
  cout << endl;

  qt1.resize(3);
  qt1.set(3, 7, 3, 7, 0);
  qt1.print();
  cout << endl;

  qt1.resize(2);
  qt1.print();
  cout << endl;

  qt1.resize(3);
  qt1.print();
  cout << endl;

  qt1.resize(6);
  qt1.print();
  cout << endl;

  return 0;
}
