#include "190100044_3.h"
#include <iostream>

using namespace std;

int main() {
  quad_tree qt1(2);
  quad_tree qt2(qt1);

  /* Constructor Test */
  // qt1.print();
  // cout << endl;
  // qt2.print();
  // cout << endl;

  /* Set Test 1 */
  // qt1.print();
  // cout << endl;
  // qt1.set(0, 0, 2, 2, 1);
  // qt1.print();
  // cout << endl;
  // qt1.set(1, 2, 2, 2, 0);
  // qt1.print();
  // cout << endl;

  /* Set Test 2 */
  // qt2.print();
  // cout << endl;
  // qt2.set(0, 0, 2, 3, 1);
  // qt2.print();
  // cout << endl;
  // qt2.set(1, 2, 3, 2, 0);
  // qt2.print();
  // cout << endl;

  /* Overlap (OR) Test */
  // qt1.set(1, 1, 3, 3, 1);
  // qt1.set(3, 1, 3, 1, 0);
  // qt1.set(0, 2, 0, 2, 1);
  // qt1.print();
  // cout << endl;
  // qt2.set(0, 0, 0, 3, 1);
  // qt2.set(0, 2, 1, 3, 1);
  // qt2.set(0, 2, 0, 2, 0);
  // qt2.print();
  // cout << endl;
  // qt2.overlap(qt1);
  // qt2.print();
  // cout << endl;
  // qt2.set(0, 1, 2, 3, 0);
  // qt2.print();
  // cout << endl;

  /* Intersect (AND) Test */
  // qt1.set(1, 1, 3, 3, 1);
  // qt1.set(3, 1, 3, 1, 0);
  // qt1.set(0, 2, 0, 2, 1);
  // qt1.print();
  // cout << endl;
  // qt2.set(0, 0, 0, 3, 1);
  // qt2.set(0, 2, 1, 3, 1);
  // qt2.set(0, 2, 0, 2, 0);
  // qt2.print();
  // cout << endl;
  // qt2.intersect(qt1);
  // qt2.print();
  // cout << endl;
  // qt2.set(0, 1, 2, 2, 1);
  // qt2.print();
  // cout << endl;

  return 0;
}
