#include <iostream>
#include <string>

// a=97
int size;

namespace first {
int **mat_nn;

long long int *matrix_mul(long long int *in_mat, long long int &sum) {
  long long int *out_mat = new long long int[size];
  for (int i = 0; i < size; i++) {
    out_mat[i] = 0;
    for (int j = 0; j < size; j++) {
      out_mat[i] += mat_nn[i][j] * in_mat[j];
    }
    sum += out_mat[i];
  }
  return out_mat;
}

bool mat_len_equal(long long int *mat1, long long int *mat2) {
  long long int count1 = 0, count2 = 0;
  for (int i = 0; i < size; i++) {
    count1 += mat1[i];
    count2 += mat2[i];
    // if (mat1[i] != mat2[i])
    //   return false;
  }
  return count1 == count2;
}

long long int general(long long int n) {
  if (n == 0) {
    return 1;
  }

  long long int len = 0;
  long long int *mat = new long long int[size];
  for (int i = 0; i < size; i++) {
    mat[i] = mat_nn[i][0];
    len += mat[i];
  }
  mat[0]--;
  long long int *mat_;
  long long int i = 1;
  int rep = 0;
  for (; (i < n) && (rep < 12); i++) {
    mat_ = matrix_mul(mat, len);
    if (mat_len_equal(mat_, mat))
      rep++;
    else
      rep = 0;
    mat = mat_;
  }
  if (i < n) {
    std::cout << "Hi\n";
    long long int count = 0;
    for (int i = 0; i < size; i++) {
      count += mat_[i];
    }
    len += (n - i) * count;
  }

  // long long int len = 0;
  // for (int i = 0; i < size; i++) {
  //   len += mat[i];
  // }
  return len;
}

void init(std::string f[]) {
  mat_nn = new int *[size];
  for (int i = 0; i < size; ++i) {
    mat_nn[i] = new int[size];
  }

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      mat_nn[i][j] = 0;
    }
  }

  for (int i = 0; i < size; i++) {
    int len = f[i].length();
    for (int j = 0; j < len; j++) {
      mat_nn[int(f[i][j]) - 97][i]++;
      // switch (f[i][j]) {
      // case 'a':
      //   mat_nn[i][0]++;
      //   break;
      // case 'b':
      //   mat_nn[i][1]++;
      //   break;
      // case 'c':
      //   mat_nn[i][2]++;
      //   break;
      // case 'd':
      //   mat_nn[i][3]++;
      //   break;
      // case 'e':
      //   mat_nn[i][4]++;
      //   break;
      // case 'f':
      //   mat_nn[i][5]++;
      //   break;
      // default:
      //   break;
      // }
    }
  }
}

} // namespace first

int main() {
  std::cin >> size;

  std::string f[size];
  for (int i = 0; i < size; i++) {
    std::cin >> f[i];
  }
  first::init(f);

  long long int n;
  std::cin >> n;
  // for (int i = 0; i < 100; i++) first::general(n);
  std::cout << first::general(n) << std::endl;

  // first::mat_nn = new int *[n];
  // for (int i = 0; i < n; ++i)
  //   first::mat_nn[i] = new int[n];

  // for (int i = 0; i < n; i++) {
  //   for (int j = 0; j < n; j++) {
  //     std::cin >> first::mat_nn[i][j];
  //   }
  // }

  // int *in = new int[n];
  // for (int i = 0; i < n; i++) {
  //   std::cin >> in[i];
  // }

  // int *out = first::matrix_mul(in, n);

  // for (int i = 0; i < n; i++) {
  //   std::cout << out[i] << " ";
  // }
  // std::cout << std::endl;

  delete first::mat_nn;
  return 0;
}
