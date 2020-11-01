#include "190100044_3.h"

using namespace std;

int main() {
  quad_tree qt1(1);
  quad_tree qt2(qt1);

  /* Constructor Test */
  // qt1.print();
  // cout << endl;
  // qt2.print();
  // cout << endl;

  /* Set Test */
  // qt1.print();
  // cout << endl;
  // qt1.set(0, 0, 1, 1, 1);
  // qt1.print();
  // cout << endl;
  // qt1.set(0, 0, 1, 0, 0);
  // qt1.print();
  // cout << endl;
  // qt1.set(0, 0, 0, 1, 1);
  // qt1.print();
  // cout << endl;

  /* Complement Test */
  // qt1.set(0, 0, 0, 0, 1);
  // qt1.print();
  // cout << endl;
  // qt1.complement();
  // qt1.print();
  // cout << endl;
  // qt2.set(0, 0, 1, 0, 1);
  // qt2.print();
  // cout << endl;
  // qt2.complement();
  // qt2.print();
  // cout << endl;

  /* Overlap (OR) Test */
  // qt1.set(0, 0, 0, 1, 1);
  // qt1.print();
  // cout << endl;
  // qt2.set(0, 1, 1, 1, 1);
  // qt2.print();
  // cout << endl;
  // qt2.overlap(qt1);
  // qt2.print();
  // cout << endl;

  /* Intersect (AND) Test */
  // qt1.set(0, 0, 0, 1, 1);
  // qt1.print();
  // cout << endl;
  // qt2.set(0, 1, 1, 1, 1);
  // qt2.print();
  // cout << endl;
  // qt2.intersect(qt1);
  // qt2.print();
  // cout << endl;

  return 0;
}
