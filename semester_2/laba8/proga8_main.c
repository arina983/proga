#include "matrix_test8.h"

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