#include <stdio.h>

void print_matrix(int n, int m, double matrix[n][m]) {
    for (int i = 0; i < n; i++) {
         for (int j = 0; j < n; j++) {
             printf("%lf", matrix[i][j]);
         }
         printf("\n");
    }
}

double determinant(int N, double M[N][N]) {
    if (N == 1) return M[0][0];
    if (N == 2) return M[0][0] * M[1][1] - M[0][1] * M[1][0];
    if (N == 3) {
        return M[0][0] * M[1][1] * M[2][2] + M[0][1] * M[1][2] * M[2][0] +
               M[0][2] * M[1][0] * M[2][1] - M[0][2] * M[1][1] * M[2][0] - 
               M[0][0] * M[1][2] * M[2][1] - M[0][1] * M[1][0] * M[2][2];
    }   
    return 0;
}
int main() {
    int n;
    double matrix[3][3];
    printf("Введите размер матрицы (2 или 3):");
    scanf("%d", &n);
    printf("Введите коэффициенты матрицы:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &matrix[i][j]);
        }
    }
printf("Матрица:\n");
print_matrix(n, n, matrix);
//вычисление определителя матрицы
double det = determinant(n, matrix);
printf("Определитель матрицы: %.3lf\n", det);

  return 0;
}
