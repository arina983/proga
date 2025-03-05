#include <stdio.h>

void InsertSort(int n, int A[n]) {
    int C = 0;
    int M = 0;
    for (int i = 1; i < n; i++) {
        int temp = A[i];
        M++;
        int j = i - 1;
        while (j >= 0 && A[j] > temp) {
            C++;
            A[j + 1] = A[j];
            M++;
            j--;
        }
        C++;
        A[j + 1] = temp;
        M++;
    }
    printf("Comparisons: %d, Moves: %d\n", C, M);
}

int main() {
    int a[] = {4, 2};
    int n = sizeof(a) / sizeof(a[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    InsertSort(n, a);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}
