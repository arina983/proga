#include "matrix.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Ошибка: %s не введено имя файла\n", argv[0]);
        return 1;
    }

    int n;
    double **matrix = read_matrix(argv[1], &n);
    if (!matrix) {
        return 1;
    }

    printf("Исходная матрица (%dx%d):\n", n, n);
    print_matrix_isx(n, matrix);

    int error;
    double **inverse = inverse_matrix(n, matrix, &error);
    
    if (error) {
        printf("\nOбратной матрицы не существует.\n");
    } else {
        printf("\nОбратная матрица:\n");
        print_matrix(n, inverse);
        
        verify_inverse(n, matrix, inverse);
    }

    free_matrix(n, matrix);
    if (inverse) free_matrix(n, inverse);
    
    return 0;
}