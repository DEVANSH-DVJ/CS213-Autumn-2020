#ifndef _QUADTREE_H_
#define _QUADTREE_H_

#include <iostream>

class quad_tree {
private:
  int n = -1;
  long long width = 0;

  quad_tree *sub00;
  quad_tree *sub01;
  quad_tree *sub10;
  quad_tree *sub11;

  int value = -1;

public:
  quad_tree(int n);
  quad_tree(int n, int b); // helper constructor
  quad_tree(quad_tree const &Q);
  ~quad_tree();

  void set(int x1, int y1, int x2, int y2, int b);
  int get(int x1, int y1) const;
  int size() const;

  void overlap(quad_tree const &Q);
  void intersect(quad_tree &Q);
  void complement();

  void resize(int m);
  void extract(int x1, int y1, int m);

  // helper functions
  quad_tree *ex(int x1, int y1, int m) const;
  void collapse();
  long long count() const;
  long long count_nodes() const;
  void print() const;
};

quad_tree::quad_tree(int n) {
  this->sub00 = NULL;
  this->sub01 = NULL;
  this->sub10 = NULL;
  this->sub11 = NULL;
  this->n = n;
  this->width = (1 << n);

  this->value = 0;

  return;
}

quad_tree::quad_tree(int n, int b) {
  this->sub00 = NULL;
  this->sub01 = NULL;
  this->sub10 = NULL;
  this->sub11 = NULL;
  this->n = n;
  this->width = (1 << n);

  this->value = b;

  return;
}

quad_tree::quad_tree(quad_tree const &Q) {
  this->n = Q.n;
  this->width = Q.width;
  this->value = Q.value;

  if (this->value != -1) {
    this->sub00 = NULL;
    this->sub01 = NULL;
    this->sub10 = NULL;
    this->sub11 = NULL;
  } else {
    this->sub00 = new quad_tree(*Q.sub00);
    this->sub01 = new quad_tree(*Q.sub01);
    this->sub10 = new quad_tree(*Q.sub10);
    this->sub11 = new quad_tree(*Q.sub11);
  }

  return;
}

quad_tree::~quad_tree() {
  delete this->sub00;
  delete this->sub01;
  delete this->sub10;
  delete this->sub11;
  return;
}

void quad_tree::set(int x1, int y1, int x2, int y2, int b) {
  if (x1 == 0 && y1 == 0 && x2 == (this->width - 1) &&
      y2 == (this->width - 1)) {
    delete this->sub00;
    delete this->sub01;
    delete this->sub10;
    delete this->sub11;
    this->sub00 = NULL;
    this->sub01 = NULL;
    this->sub10 = NULL;
    this->sub11 = NULL;
    this->value = b;
    return;
  }

  int half = this->width / 2;

  if (this->value != -1) {
    this->sub00 = new quad_tree(n - 1, this->value);
    this->sub01 = new quad_tree(n - 1, this->value);
    this->sub10 = new quad_tree(n - 1, this->value);
    this->sub11 = new quad_tree(n - 1, this->value);
    this->value = -1;
  }
  if (x1 < half && y1 < half) {
    // std::cout << "00" << std::endl;
    int x_ = x2, y_ = y2;
    if (x2 >= half) {
      x_ = (half)-1;
    }
    if (y2 >= half) {
      y_ = (half)-1;
    }
    this->sub00->set(x1, y1, x_, y_, b);
  }
  if (x1 < half && y2 >= half) {
    // std::cout << "01" << std::endl;
    int x_ = x2, y_ = y1 - half;
    if (x2 >= half) {
      x_ = (half)-1;
    }
    if (y1 < half) {
      y_ = 0;
    }
    this->sub01->set(x1, y_, x_, y2 - half, b);
  }
  if (x2 >= half && y1 < half) {
    // std::cout << "10" << std::endl;
    int x_ = x1 - half, y_ = y2;
    if (x1 < half) {
      x_ = 0;
    }
    if (y2 >= half) {
      y_ = (half)-1;
    }
    this->sub10->set(x_, y1, x2 - half, y_, b);
  }
  if (x2 >= half && y2 >= half) {
    // std::cout << "11" << std::endl;
    int x_ = x1 - half, y_ = y1 - half;
    if (x1 < half) {
      x_ = 0;
    }
    if (y1 < half) {
      y_ = 0;
    }
    this->sub11->set(x_, y_, x2 - half, y2 - half, b);
  }
  this->collapse();

  return;
}

int quad_tree::get(int x, int y) const {
  if (this->value != -1) {
    return this->value;
  }

  int half = this->width / 2;
  if (x < half) {
    if (y < half) {
      return this->sub00->get(x, y);
    } else {
      return this->sub01->get(x, y - half);
    }
  } else {
    if (y < half) {
      return this->sub10->get(x - half, y);
    } else {
      return this->sub11->get(x - half, y - half);
    }
  }
}

int quad_tree::size() const { return n; }

void quad_tree::overlap(quad_tree const &Q) {
  if (this->value == 0) {
    if (Q.value != -1) {
      this->value = Q.value;
      return; // this->value = 0 and Q->value = 0,1
    } else {
      this->sub00 = new quad_tree(*Q.sub00);
      this->sub01 = new quad_tree(*Q.sub01);
      this->sub10 = new quad_tree(*Q.sub10);
      this->sub11 = new quad_tree(*Q.sub11);
      this->value = -1;
      return; // this->value = 0 and Q->value = -1
    }
  } else if (this->value == 1) {
    return; // this->value = 1 and Q->value = 0,1,-1
  } else {
    if (Q.value == 0) {
      return; // this->value = -1 and Q->value = 0
    } else if (Q.value == 1) {
      delete this->sub00;
      delete this->sub01;
      delete this->sub10;
      delete this->sub11;
      this->sub00 = NULL;
      this->sub01 = NULL;
      this->sub10 = NULL;
      this->sub11 = NULL;
      this->value = 1;
      return; // this->value = -1 and Q->value = 1
    } else {
      this->sub00->overlap(*Q.sub00);
      this->sub01->overlap(*Q.sub01);
      this->sub10->overlap(*Q.sub10);
      this->sub11->overlap(*Q.sub11);
      this->collapse();
      return; // this->value = -1 and Q->value = -1
    }
  }
}

void quad_tree::intersect(quad_tree &Q) {
  if (this->value == 0) {
    return; // this->value = 0 and Q->value = 0,1,-1
  } else if (this->value == 1) {
    if (Q.value != -1) {
      this->value = Q.value;
      return; // this->value = 1 and Q->value = 0,1
    } else {
      this->sub00 = new quad_tree(*Q.sub00);
      this->sub01 = new quad_tree(*Q.sub01);
      this->sub10 = new quad_tree(*Q.sub10);
      this->sub11 = new quad_tree(*Q.sub11);
      this->value = -1;
      return; // this->value = 1 and Q->value = -1
    }
  } else {
    if (Q.value == 0) {
      delete this->sub00;
      delete this->sub01;
      delete this->sub10;
      delete this->sub11;
      this->sub00 = NULL;
      this->sub01 = NULL;
      this->sub10 = NULL;
      this->sub11 = NULL;
      this->value = 0;
      return; // this->value = -1 and Q->value = 0
    } else if (Q.value == 1) {
      return; // this->value = -1 and Q->value = 1
    } else {
      this->sub00->intersect(*Q.sub00);
      this->sub01->intersect(*Q.sub01);
      this->sub10->intersect(*Q.sub10);
      this->sub11->intersect(*Q.sub11);
      this->collapse();
      return; // this->value = -1 and Q->value = -1
    }
  }
}

void quad_tree::complement() {
  if (this->value == 0) {
    this->value = 1;
    return; // value = 0
  } else if (this->value == 1) {
    this->value = 0;
    return; // value = 1
  } else {
    this->sub00->complement();
    this->sub01->complement();
    this->sub10->complement();
    this->sub11->complement();
    return; // value = -1
  }
}

void quad_tree::resize(int m) {
  if (this->n == m) {
    return; // 0 <= n = m
  } else if (this->n < m) {
    if (this->value != -1) {
      this->n = m;
      this->width = (1 << n);
      return; // 0 <= n < m and value = 0,1
    } else {
      this->sub00->resize(m - 1);
      this->sub01->resize(m - 1);
      this->sub10->resize(m - 1);
      this->sub11->resize(m - 1);
      this->n = m;
      this->width = (1 << n);
      return; // 0 <= n < m and value = -1
    }
  } else {
    if (this->value != -1) {
      this->n = m;
      this->width = (1 << n);
      return; // n > m >= 0 and value = 0,1
    } else {
      if (m == 0) {
        long long c = this->count();
        if (c < this->width * this->width / 2) {
          this->value = 0;
        } else {
          this->value = 1;
        }
        delete this->sub00;
        delete this->sub01;
        delete this->sub10;
        delete this->sub11;
        this->sub00 = NULL;
        this->sub01 = NULL;
        this->sub10 = NULL;
        this->sub11 = NULL;
        this->n = m;
        this->width = (1 << n);
        return; // n > m = 0 and value = -1
      } else {
        this->sub00->resize(m - 1);
        this->sub01->resize(m - 1);
        this->sub10->resize(m - 1);
        this->sub11->resize(m - 1);
        this->n = m;
        this->width = (1 << n);
        this->collapse();
        return; // n > m > 0 and value = -1
      }
    }
  }
}

void quad_tree::extract(int x1, int y1, int m) {
  if (this->n == m) {
    return;
  } else {
    quad_tree *qt = this->ex(x1, y1, m);
    delete this->sub00;
    delete this->sub01;
    delete this->sub10;
    delete this->sub11;
    this->sub00 = qt->sub00;
    this->sub01 = qt->sub01;
    this->sub10 = qt->sub10;
    this->sub11 = qt->sub11;
    this->value = qt->value;
    this->n = m;
    this->width = (1 << n);
    return;
  }
}

quad_tree *quad_tree::ex(int x1, int y1, int m) const {
  if (this->value != -1) {
    return new quad_tree(m, this->value);
  } else if (this->n == m) {
    return new quad_tree(*this);
  } else if (m == 0) {
    return new quad_tree(0, this->get(x1, y1));
  } else {
    int half = this->width / 2;
    if (x1 < half) {
      if (y1 < half) {
        if (x1 + (1 << m) <= half) {
          if (y1 + (1 << m) <= half) {
            // Top point in 00, Bottom point in 00
            return this->sub00->ex(x1, y1, m);
          }
        }
      } else {
        if (x1 + (1 << m) <= half) {
          // Top point in 01, Bottom point in 01
          return this->sub01->ex(x1, y1 - half, m);
        }
      }
    } else {
      if (y1 < half) {
        if (y1 + (1 << m) <= half) {
          // Top point in 10, Bottom point in 10
          return this->sub10->ex(x1 - half, y1, m);
        }
      } else {
        return this->sub11->ex(x1 - half, y1 - half, m);
      }
    }
  }
  int half_new = (1 << (m - 1)); // m > 0
  quad_tree *qt = new quad_tree(m);
  qt->value = -1;
  qt->sub00 = this->ex(x1, y1, m - 1);
  qt->sub01 = this->ex(x1, y1 + half_new, m - 1);
  qt->sub10 = this->ex(x1 + half_new, y1, m - 1);
  qt->sub11 = this->ex(x1 + half_new, y1 + half_new, m - 1);
  qt->collapse();
  return qt;
}

// quad_tree *quad_tree::ex(int x1, int y1, int m) const {
//   if (this->value != -1) {
//     return new quad_tree(m, this->value);
//   } else if (this->n == m) {
//     return new quad_tree(*this);
//   } else if (m == 0) {
//     return new quad_tree(0, this->get(x1, y1));
//   } else {
//     int half = this->width / 2;
//     if (x1 < half) {
//       if (y1 < half) { // Top point in 00
//         if (x1 + (1 << m) <= half) {
//           if (y1 + (1 << m) <= half) {
//             // Top point in 00, Bottom point in 00
//             return this->sub00->ex(x1, y1, m);
//           } else {
//             // Top point in 00, Bottom point in 01
//             int half_new = (1 << (m - 1)); // m > 0
//             if (y1 < half_new) {
//               // Top point in 00, Bottom point in 01, midaxis left of
//               halfline quad_tree *qt = new quad_tree(m); qt->value = -1;
//               qt->sub00 = this->sub00->ex(x1, y1, m - 1);
//               qt->sub01 = this->ex(x1, y1 + half_new, m - 1);
//               qt->sub10 = this->sub00->ex(x1 + half_new, y1, m - 1);
//               qt->sub11 = this->ex(x1 + half_new, y1 + half_new, m - 1);
//               qt->collapse();
//               return qt;
//             } else if (y1 > half_new) {
//               // Top point in 00, Bottom point in 01, midaxis right of
//               halfline quad_tree *qt = new quad_tree(m); qt->value = -1;
//               qt->sub00 = this->ex(x1, y1, m - 1);
//               qt->sub01 = this->sub01->ex(x1, y1 - half_new, m - 1);
//               qt->sub10 = this->ex(x1 + half_new, y1, m - 1);
//               qt->sub11 = this->sub01->ex(x1 + half_new, y1 - half_new, m -
//               1); qt->collapse(); return qt;
//             } else {
//               // Top point in 00, Bottom point in 01, midaxis on halfline
//               quad_tree *qt = new quad_tree(m);
//               qt->value = -1;
//               qt->sub00 = this->sub00->ex(x1, y1, m - 1);
//               qt->sub01 = this->sub01->ex(x1, y1 - half_new, m - 1);
//               qt->sub10 = this->sub00->ex(x1 + half_new, y1, m - 1);
//               qt->sub11 = this->sub01->ex(x1 + half_new, y1 - half_new, m -
//               1); qt->collapse(); return qt;
//             }
//           }
//         } else {
//           if (y1 + (1 << m) <= half) {
//             // Top point in 00, Bottom point in 10
//             int half_new = (1 << (m - 1)); // m > 0
//             if (x1 < half_new) {
//               // Top point in 00, Bottom point in 10, midaxis above halfline
//               quad_tree *qt = new quad_tree(m);
//               qt->value = -1;
//               qt->sub00 = this->sub00->ex(x1, y1, m - 1);
//               qt->sub01 = this->sub00->ex(x1, y1 + half_new, m - 1);
//               qt->sub10 = this->ex(x1 + half_new, y1, m - 1);
//               qt->sub11 = this->ex(x1 + half_new, y1 + half_new, m - 1);
//               qt->collapse();
//               return qt;
//             } else if (x1 > half_new) {
//               // Top point in 00, Bottom point in 10, midaxis below halfline
//               quad_tree *qt = new quad_tree(m);
//               qt->value = -1;
//               qt->sub00 = this->ex(x1, y1, m - 1);
//               qt->sub01 = this->ex(x1, y1 + half_new, m - 1);
//               qt->sub10 = this->sub10->ex(x1 - half_new, y1, m - 1);
//               qt->sub11 = this->sub10->ex(x1 - half_new, y1 + half_new, m -
//               1); qt->collapse(); return qt;
//             } else {
//               // Top point in 00, Bottom point in 10, midaxis on halfline
//               quad_tree *qt = new quad_tree(m);
//               qt->value = -1;
//               qt->sub00 = this->sub00->ex(x1, y1, m - 1);
//               qt->sub01 = this->sub00->ex(x1, y1 + half_new, m - 1);
//               qt->sub10 = this->sub10->ex(x1 - half_new, y1, m - 1);
//               qt->sub11 = this->sub10->ex(x1 - half_new, y1 + half_new, m -
//               1); qt->collapse(); return qt;
//             }
//           } else {
//             // Top point in 00, Bottom point in 11
//           }
//         }
//       } else { // Top point in 01
//         if (x1 + (1 << m) <= half) {
//           // Top point in 01, Bottom point in 01
//           return this->sub01->ex(x1, y1 - half, m);
//         } else {
//           // Top point in 01, Bottom point in 11
//           int half_new = (1 << (m - 1)); // m > 0
//           if (x1 < half_new) {
//             // Top point in 01, Bottom point in 11, midaxis above halfline
//             quad_tree *qt = new quad_tree(m);
//             qt->value = -1;
//             qt->sub00 = this->sub01->ex(x1, y1 - half, m - 1);
//             qt->sub01 = this->sub01->ex(x1, y1 - half_new, m - 1);
//             qt->sub10 = this->ex(x1 + half_new, y1, m - 1);
//             qt->sub11 = this->ex(x1 + half_new, y1 + half_new, m - 1);
//             qt->collapse();
//             return qt;
//           } else if (x1 > half_new) {
//             // Top point in 01, Bottom point in 11, midaxis below halfline
//             quad_tree *qt = new quad_tree(m);
//             qt->value = -1;
//             qt->sub00 = this->ex(x1, y1, m - 1);
//             qt->sub01 = this->ex(x1, y1 + half_new, m - 1);
//             qt->sub10 = this->sub11->ex(x1 - half_new, y1 - half, m - 1);
//             qt->sub11 = this->sub11->ex(x1 - half_new, y1 - half_new, m - 1);
//             qt->collapse();
//             return qt;
//           } else {
//             // Top point in 01, Bottom point in 11, midaxis on halfline
//             quad_tree *qt = new quad_tree(m);
//             qt->value = -1;
//             qt->sub00 = this->sub01->ex(x1, y1 - half, m - 1);
//             qt->sub01 = this->sub01->ex(x1, y1 - half_new, m - 1);
//             qt->sub10 = this->sub11->ex(x1 - half_new, y1 - half, m - 1);
//             qt->sub11 = this->sub11->ex(x1 - half_new, y1 - half_new, m - 1);
//             qt->collapse();
//             return qt;
//           }
//         }
//       }
//     } else {
//       if (y1 < half) { // Top point in 10
//         if (y1 + (1 << m) <= half) {
//           // Top point in 10, Bottom point in 10
//           return this->sub10->ex(x1 - half, y1, m);
//         } else {
//           // Top point in 10, Bottom point in 11
//           int half_new = (1 << (m - 1)); // m > 0
//           if (y1 < half_new) {
//             // Top point in 10, Bottom point in 11, midaxis left of halfline
//             quad_tree *qt = new quad_tree(m);
//             qt->value = -1;
//             qt->sub00 = this->sub10->ex(x1 - half, y1, m - 1);
//             qt->sub01 = this->ex(x1, y1 + half_new, m - 1);
//             qt->sub10 = this->sub10->ex(x1 - half_new, y1, m - 1);
//             qt->sub11 = this->ex(x1 + half_new, y1 + half_new, m - 1);
//             qt->collapse();
//             return qt;
//           } else if (y1 > half_new) {
//             // Top point in 10, Bottom point in 11, midaxis right of halfline
//             quad_tree *qt = new quad_tree(m);
//             qt->value = -1;
//             qt->sub00 = this->ex(x1, y1, m - 1);
//             qt->sub01 = this->sub11->ex(x1 - half, y1 - half_new, m - 1);
//             qt->sub10 = this->ex(x1 + half_new, y1, m - 1);
//             qt->sub11 = this->sub11->ex(x1 - half_new, y1 - half_new, m - 1);
//             qt->collapse();
//             return qt;
//           } else {
//             // Top point in 10, Bottom point in 11, midaxis on halfline
//             quad_tree *qt = new quad_tree(m);
//             qt->value = -1;
//             qt->sub00 = this->sub10->ex(x1 - half, y1, m - 1);
//             qt->sub01 = this->sub11->ex(x1 - half, y1 - half_new, m - 1);
//             qt->sub10 = this->sub10->ex(x1 - half_new, y1, m - 1);
//             qt->sub11 = this->sub11->ex(x1 - half_new, y1 - half_new, m - 1);
//             qt->collapse();
//             return qt;
//           }
//         }
//       } else { // Top point in 11
//         return this->sub11->ex(x1 - half, y1 - half, m);
//       }
//     }
//   }
// }

void quad_tree::collapse() {
  if (this->value != -1) {
    return;
  }

  if (this->sub00->value == 0 && this->sub01->value == 0 &&
      this->sub10->value == 0 && this->sub11->value == 0) {
    delete this->sub00;
    delete this->sub01;
    delete this->sub10;
    delete this->sub11;
    this->sub00 = NULL;
    this->sub01 = NULL;
    this->sub10 = NULL;
    this->sub11 = NULL;
    this->value = 0;
  } else if (this->sub00->value == 1 && this->sub01->value == 1 &&
             this->sub10->value == 1 && this->sub11->value == 1) {
    delete this->sub00;
    delete this->sub01;
    delete this->sub10;
    delete this->sub11;
    this->sub00 = NULL;
    this->sub01 = NULL;
    this->sub10 = NULL;
    this->sub11 = NULL;
    this->value = 1;
  }
  return;
}

long long quad_tree::count() const {
  if (this->value == 0) {
    return 0;
  } else if (this->value == 1) {
    return this->width * this->width;
  } else {
    return this->sub00->count() + this->sub01->count() + this->sub10->count() +
           this->sub11->count();
  }
}

long long quad_tree::count_nodes() const {
  if (this->value != -1) {
    return 1;
  } else {
    return 1 + this->sub00->count_nodes() + this->sub01->count_nodes() +
           this->sub10->count_nodes() + this->sub11->count_nodes();
  }
}

void quad_tree::print() const {
  std::cout << "N: " << n << std::endl;
  std::cout << "Width: " << width << std::endl;
  std::cout << "Nodes: " << this->count_nodes() << std::endl;
  for (int i = 0; i < this->width; i++) {
    for (int j = 0; j < this->width; j++) {
      std::cout << this->get(i, j) << " ";
    }
    std::cout << std::endl;
  }
  return;
}

#endif // _QUADTREE_H_
