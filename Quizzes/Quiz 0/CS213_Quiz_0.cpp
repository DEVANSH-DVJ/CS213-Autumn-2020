#include <iostream>

int num_blocks(int p[], int n) {
    int m, M, num = 0;
    for (int i = 0; i < n; i++) {
        m = n + 1;
        M = 0;
        for (int j = i; j < n; j++) {
            if (p[j] < m) m = p[j];
            if (M < p[j]) M = p[j];
            if (M == m + j - i) num++;
        }
    }
    return num;
}

int main() {
    int arr[] = {3, 1, 5, 4, 2, 6, 7};
    std::cout << num_blocks(arr, 7) << std::endl;
    return 0;
}
