#ifndef _QUADTREE_H_
#define _QUADTREE_H_

#include <iostream>

class quad_tree {
private:
  int n = -1, width = 0;

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

  // helper functions
  void collapse();
  long count();
  long count_nodes();
  void print();
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

  if (Q.sub00 != NULL) {
    this->sub00 = new quad_tree(*Q.sub00);
  } else {
    this->sub00 = NULL;
  }
  if (Q.sub01 != NULL) {
    this->sub01 = new quad_tree(*Q.sub01);
  } else {
    this->sub01 = NULL;
  }
  if (Q.sub10 != NULL) {
    this->sub10 = new quad_tree(*Q.sub10);
  } else {
    this->sub10 = NULL;
  }
  if (Q.sub11 != NULL) {
    this->sub11 = new quad_tree(*Q.sub11);
  } else {
    this->sub11 = NULL;
  }

  return;
}

quad_tree::~quad_tree() {
  if (this->sub00 != NULL) {
    delete this->sub00;
  }
  if (this->sub01 != NULL) {
    delete this->sub01;
  }
  if (this->sub10 != NULL) {
    delete this->sub10;
  }
  if (this->sub11 != NULL) {
    delete this->sub11;
  }
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

  if (this->value != -1) {
    this->sub00 = new quad_tree(n - 1, this->value);
    this->sub01 = new quad_tree(n - 1, this->value);
    this->sub10 = new quad_tree(n - 1, this->value);
    this->sub11 = new quad_tree(n - 1, this->value);
    this->value = -1;
  }
  if (x1 < this->width / 2 && y1 < this->width / 2) {
    // std::cout << "00" << std::endl;
    int x_ = x2, y_ = y2;
    if (x2 >= this->width / 2) {
      x_ = (this->width / 2) - 1;
    }
    if (y2 >= this->width / 2) {
      y_ = (this->width / 2) - 1;
    }
    this->sub00->set(x1, y1, x_, y_, b);
  }
  if (x1 < this->width / 2 && y2 >= this->width / 2) {
    // std::cout << "01" << std::endl;
    int x_ = x2, y_ = y1 - this->width / 2;
    if (x2 >= this->width / 2) {
      x_ = (this->width / 2) - 1;
    }
    if (y1 < this->width / 2) {
      y_ = 0;
    }
    this->sub01->set(x1, y_, x_, y2 - this->width / 2, b);
  }
  if (x2 >= this->width / 2 && y1 < this->width / 2) {
    // std::cout << "10" << std::endl;
    int x_ = x1 - this->width / 2, y_ = y2;
    if (x1 < this->width / 2) {
      x_ = 0;
    }
    if (y2 >= this->width / 2) {
      y_ = (this->width / 2) - 1;
    }
    this->sub10->set(x_, y1, x2 - this->width / 2, y_, b);
  }
  if (x2 >= this->width / 2 && y2 >= this->width / 2) {
    // std::cout << "11" << std::endl;
    int x_ = x1 - this->width / 2, y_ = y1 - this->width / 2;
    if (x1 < this->width / 2) {
      x_ = 0;
    }
    if (y1 < this->width / 2) {
      y_ = 0;
    }
    this->sub11->set(x_, y_, x2 - this->width / 2, y2 - this->width / 2, b);
  }
  this->collapse();

  return;
}

int quad_tree::get(int x, int y) const {
  if (this->value != -1) {
    return this->value;
  }
  if (x < this->width / 2) {
    if (y < this->width / 2) {
      return this->sub00->get(x, y);
    } else {
      return this->sub01->get(x, y - this->width / 2);
    }
  } else {
    if (y < this->width / 2) {
      return this->sub10->get(x - this->width / 2, y);
    } else {
      return this->sub11->get(x - this->width / 2, y - this->width / 2);
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
        long c = this->count();
        if (c < long(this->width) * long(this->width) / 2) {
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

long quad_tree::count() {
  if (this->value == 0) {
    return long(0);
  } else if (this->value == 1) {
    return long(this->width) * long(this->width);
  } else {
    return this->sub00->count() + this->sub01->count() + this->sub10->count() +
           this->sub11->count();
  }
}

long quad_tree::count_nodes() {
  if (this->value != -1) {
    return long(1);
  } else {
    return long(1) + this->sub00->count_nodes() + this->sub01->count_nodes() +
           this->sub10->count_nodes() + this->sub11->count_nodes();
  }
}

void quad_tree::print() {
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
