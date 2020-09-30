#include <iostream>

class good_function {
private:
  int n;
  int *arr;

public:
  good_function() {
    n = 8;
    arr = new int[8]{4, 5, 7, 6, 6, 1, 3, 4};
  }

  ~good_function() { delete arr; }

  int operator()(int i) { return arr[i]; }

  int size() { return n; }
};

int duplicate(good_function f) {
  int p = 0;

  for (int i = 1; i < f.size(); i++)
    p = f(p);

  // std::cout << p << ";;;; 1\n";

  int q = f(p), l = 1;

  // std::cout << q << ";;;; 2\n";

  while (p - q) {
    q = f(q);
    l = l + 1;
  }

  // std::cout << l << ";;;; 3\n";

  p = q = 0;

  for (int i = 0; i < l; i++)
    q = f(q);

  while (p - q) {
    p = f(p);
    q = f(q);
    // std::cout << "Loop;;" << p << ";;" << q << "\n";
  }

  return p;
}

int main() {
  good_function f;
  // std::cout << f.size() << f(4);

  std::cout << duplicate(f) << std::endl;
  return 0;
}
