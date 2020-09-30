#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <vector>

namespace {
typedef std::vector<int> IntVector;

struct Interval {
    int left;
    int right;
};

Interval MakeInterval(int left, int right) {
    Interval i = {left, right};
    return i;
}

typedef std::vector<Interval> IntervalVector;

enum Direction {
    kLeft,
    kRight,
};

// Finds the valid intervals obtained by starting with [pi[mid],
// pi[mid]] and repeatedly extending in direction dir
//
// O(right_boundary - left_boundary)
void FindExtensions(const IntVector& pi, const IntVector& pi_inv, int left_boundary, int right_boundary, Direction dir,
                    IntervalVector* extensions) {
    int mid = left_boundary + (right_boundary - left_boundary) / 2;
    int left = mid;
    int right = mid;
    int lower = pi[mid];
    int upper = pi[mid];
    std::queue<int> worklist;
    while (true) {
        if (worklist.empty()) {
            extensions->push_back(MakeInterval(left, right));
            if (dir == kLeft) {
                if (left == left_boundary) break;
                --left;
                worklist.push(left);
            } else {
                if (right == right_boundary) break;
                ++right;
                worklist.push(right);
            }
        } else {
            int i = worklist.front();
            worklist.pop();
            if (i < left) {
                if (i < left_boundary) break;
                for (int j = left - 1; j >= i; --j) worklist.push(j);
                left = i;
            } else if (right < i) {
                if (right_boundary < i) break;
                for (int j = right + 1; j <= i; ++j) worklist.push(j);
                right = i;
            }
            int x = pi[i];
            if (x < lower) {
                for (int y = lower - 1; y > x; --y) worklist.push(pi_inv[y]);
                lower = x;
            } else if (upper < x) {
                for (int y = upper + 1; y < x; ++y) worklist.push(pi_inv[y]);
                upper = x;
            }
        }
    }
}

int CountValidRecursive(const IntVector& pi, const IntVector& pi_inv, int left, int right) {
    if (right < left) return 0;
    int mid = left + (right - left) / 2;
    int count = CountValidRecursive(pi, pi_inv, left, mid - 1) + CountValidRecursive(pi, pi_inv, mid + 1, right);
    IntervalVector left_exts;
    FindExtensions(pi, pi_inv, left, right, kLeft, &left_exts);
    IntervalVector right_exts;
    FindExtensions(pi, pi_inv, left, right, kRight, &right_exts);
    typedef IntervalVector::const_iterator IVci;
    IVci first_good = right_exts.begin();
    IVci first_bad = right_exts.begin();
    for (IVci ext = left_exts.begin(); ext != left_exts.end(); ++ext) {
        while (first_good != right_exts.end() && first_good->right < ext->right) {
            ++first_good;
        }
        if (first_good == right_exts.end()) break;
        while (first_bad != right_exts.end() && ext->left <= first_bad->left) {
            ++first_bad;
        }
        count += std::distance(first_good, first_bad);
    }
    return count;
}

// Counts the number of intervals in pi that consist of consecutive
// integers
//
// O(n log n)
int CountValid(const IntVector& pi) {
    int n = pi.size();
    IntVector pi_inv(n, -1);
    // Validate and invert pi
    for (int i = 0; i < n; ++i) {
        if (pi[i] < 0 || pi[i] >= n || pi_inv[pi[i]] != -1) {
            throw std::runtime_error("Invalid permutation of {0, ..., n - 1}");
        }
        pi_inv[pi[i]] = i;
    }
    return CountValidRecursive(pi, pi_inv, 0, n - 1);
}

// For testing purposes
int SlowCountValid(const IntVector& pi) {
    int count = 0;
    int n = pi.size();
    for (int left = 0; left < n; ++left) {
        for (int right = left; right < n; ++right) {
            int lower = pi[left];
            int upper = pi[left];
            for (int i = left + 1; i <= right; ++i) {
                if (pi[i] < lower) {
                    lower = pi[i];
                } else if (pi[i] > upper) {
                    upper = pi[i];
                }
            }
            if (upper - lower == right - left) ++count;
        }
    }
    return count;
}
}  // namespace

int main() {
    int src[] = {0, 1, 2, 6, 4, 3, 5};

    std::vector<int> pi(std::begin(src), std::end(src));

    for (int i : pi) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    fprintf(stdout, "%d\n", CountValid(pi));
    // if (SlowCountValid(pi) != CountValid(pi)) {
    //   fprintf(stderr, "Bad permutation:");
    //   for (IntVector::const_iterator x = pi.begin(); x != pi.end(); ++x) {
    //     fprintf(stderr, " %d", *x);
    //   }
    //   fputc('\n', stderr);
    // }
}
