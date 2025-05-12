#include <stdio.h>
#include "matrix_test8.h"

void matrix(int n, int m, int arr[n][m]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf(" %d", arr[i][j]);
        }
        printf("\n");
    }
}

int determinant(int N, int arr[N][N]) {
    if (N == 3) {
        return arr[0][0] * arr[1][1] * arr[2][2] + 
               arr[0][1] * arr[1][2] * arr[2][0] + 
               arr[1][0] * arr[2][1] * arr[0][2] - 
               arr[0][2] * arr[1][1] * arr[2][0] - 
               arr[0][0] * arr[2][1] * arr[1][2] - 
               arr[1][0] * arr[0][1] * arr[2][2];
    } else if (N == 2) {
        return arr[0][0] * arr[1][1] - arr[0][1] * arr[1][0];
    } else if (N == 1) {
        return arr[0][0];
    }
    return 0;
}

void Kramer(int N, int arr[N][N], int B[N]) {
    if (N == 2) {
        int opr = determinant(N, arr);
        if (opr == 0) {
            printf("Система не имеет единственного решения\n");
            return;
        }

        int opr1 = B[0] * arr[1][1] - B[1] * arr[0][1]; 
        int opr2 = B[1] * arr[0][0] - B[0] * arr[1][0];  

        double x1 = (double)opr1 / opr;
        double x2 = (double)opr2 / opr;

        printf("Решение системы:\n");
        printf("x1 = %.2f, x2 = %.2f\n", x1, x2);

    } else if (N == 3) {
        int opr = determinant(N, arr);
        if (opr == 0) {
            printf("Система не имеет единственного решения\n");
            return;
        }

        int opr1 = B[0] * (arr[1][1] * arr[2][2] - arr[1][2] * arr[2][1]) -
                   arr[0][1] * (B[1] * arr[2][2] - arr[1][2] * B[2]) +
                   arr[0][2] * (B[1] * arr[2][1] - arr[1][1] * B[2]);

        int opr2 = arr[0][0] * (B[1] * arr[2][2] - arr[1][2] * B[2]) -
                   B[0] * (arr[1][0] * arr[2][2] - arr[1][2] * arr[2][0]) +
                   arr[0][2] * (arr[1][0] * B[2] - B[1] * arr[2][0]);

        int opr3 = arr[0][0] * (arr[1][1] * B[2] - B[1] * arr[2][1]) -
                   arr[0][1] * (arr[1][0] * B[2] - B[1] * arr[2][0]) +
                   B[0] * (arr[1][0] * arr[2][1] - arr[1][1] * arr[2][0]);

        double x1 = (double)opr1 / opr;
        double x2 = (double)opr2 / opr;
        double x3 = (double)opr3 / opr;

        printf("Решение системы:\n");
        printf("x1 = %.2f, x2 = %.2f, x3 = %.2f\n", x1, x2, x3);

    } else {
        printf("Недопустимый размер матрицы\n");
    }
}