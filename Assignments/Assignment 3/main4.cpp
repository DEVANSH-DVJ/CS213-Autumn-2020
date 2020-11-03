#include "190100044_3.h"

using namespace std;

int main() {
  quad_tree qt1(5);
  qt1.set(0, 2, 20, 31, 1);
  qt1.set(4, 5, 17, 15, 0);
  qt1.print();
  cout << endl;

  qt1.resize(20);
  qt1.extract(0, 1400, 19);
  qt1.resize(5);
  qt1.print();
  cout << endl;

  return 0;
}
