#include <stdio.h>
void matrix(int n, int m, int arr[n][m]){
    for (int i = 0; i < n; i ++){
        for (int j = 0; j < m; j ++){
            printf(" %d", arr[i][j]);
        }
        printf("\n");
    }
}
int determinant(int N, int arr[N][N]){
    int det = 0;
    if (N == 3){
        det = arr[0][0] * arr[1][1] * arr[2][2] + arr[0][1] * arr[1][2] * arr[2][0] + arr[1][0] * arr[2][1] * arr[0][2] - arr[0][2] * arr[1][1] * arr[2][0] - arr[0][0] * arr[2][1] * arr[1][2] - arr[1][0] * arr[0][1] * arr[2][2];
    } else if (N == 2){
        det = arr[0][0] * arr[1][1] - arr[0][1] * arr[1][0]; 
    } else {
        det = arr[0][0];
        return 0;
    }
    return det;
}
void Kramer(int N, int arr[N][N], int B[N]){
    if (N == 2) {
        int opr = determinant(N, arr);
        if( opr == 0){
            printf("Система не имеет единственного решения\n");
            return;
        }

        int opr1 = B[1] * arr[0][0] - B[0]* arr[1][0];
        int opr2 = B[0] * arr[1][1] - B[1] * arr[0][1];

        double x1 = (double)opr1 / opr;
        double x2 = (double)opr2 / opr;

        printf("Решение системы:\n");
        printf("x1 = %.2f, ", x1);
        printf("x2 = %.2f\n", x2);

    } else if (N == 3){
        int opr = determinant(N, arr);
        if(opr == 0){
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
        printf("x1 = %.2f, ", x1);
        printf("x2 = %.2f, ", x2);
        printf("x3 = %.2f\n", x3);

    } else {
        printf("Недопустимый размер матрицы\n");
    }
}
int main() {
    int N;
    printf("Введите размер матрицы (от 1 до 3): ");
    scanf("%d", &N);
     if (N < 1 || N > 3){
        printf("Недопустимый размер матрицы\n");
        return 1;
    }
    int arr[N][N];
    int B[N];
    printf("Введите элементы матрицы:\n");
    for (int i = 0; i < N; i ++) {
        for (int j = 0; j < N; j ++){
            printf("arr[%d][%d] = ", i, j);
            scanf("%d", &arr[i][j]);
        }
    }
    printf("Введите вектор свободных членов:\n");
    for (int i = 0; i < N; i ++) {
        printf("B[%d] = ", i);
        scanf("%d", &B[i]);
    }
    printf("Матрица:\n");
    matrix(N, N, arr);
    int det = determinant(N, arr);
    printf("Определитель матрицы: %d\n", det);

    Kramer(N, arr, B);

    return 0;
}