#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define EPSILON 1e-10 // для учета погрешности вычислений
#define MAX_SIZE 100

// Объявления функций
double** memory_matrix(int n, int m);
void free_matrix(int n, double **matrix);
double** read_matrix(const char *filename, int *n);
void print_matrix(int n, double **matrix);
double** inverse_matrix(int n, double **matrix, int *error);
void verify_inverse(int n, double **A, double **A_inv);

// Функция для выделения памяти под матрицу
double** memory_matrix(int n, int m) {
    double **matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double*)malloc(m * sizeof(double));
    }
    return matrix;
}

// Функция для освобождения памяти матрицы
void free_matrix(int n, double **matrix) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Функция для чтения матрицы из файла
double** read_matrix(const char *filename, int *n) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Ошибка: не удалось открыть файл %s\n", filename);
        return NULL;
    }

    char line[4096];
    *n = 0;
    int cols = 0;
    double **matrix = memory_matrix(MAX_SIZE, MAX_SIZE);
    
    while (fgets(line, sizeof(line), file) && *n < MAX_SIZE) {
        char *token = strtok(line, " \t\n"); // Разбиение на токены
        int current_cols = 0;
        
        while (token != NULL && current_cols < MAX_SIZE) {
            if (*n == 0) {
                matrix[*n][current_cols] = atof(token); // Преобразование в числа
            } else {
                if (current_cols >= cols) {
                    fprintf(stderr, "Ошибка: матрица не квадратная\n");
                    fclose(file);
                    free_matrix(MAX_SIZE, matrix);
                    return NULL;
                }
                matrix[*n][current_cols] = atof(token);
            }
            current_cols++;
            token = strtok(NULL, " \t\n");
        }
        
        if (*n == 0) {
            cols = current_cols;
        } else if (current_cols != cols) {
            fprintf(stderr, "Ошибка: матрица не квадратная\n");
            fclose(file);
            free_matrix(MAX_SIZE, matrix);
            return NULL;
        }
        
        (*n)++;
    }
    
    fclose(file);
    
    if (*n != cols) {
        fprintf(stderr, "Ошибка: матрица не квадратная (%dx%d)\n", *n, cols);
        free_matrix(MAX_SIZE, matrix);
        return NULL;
    }
    
    // Создаем матрицу нужного размера
    double **result = memory_matrix(*n, *n);
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            result[i][j] = matrix[i][j];
        }
    }
    
    free_matrix(MAX_SIZE, matrix);
    return result;
}

// Функция для вывода матрицы (округление до 3 знаков)
void print_matrix(int n, double **matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.3f ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Функция для вывода матрицы (без округления)
void print_matrix_isx(int n, double **matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.0f ", matrix[i][j]);
        }
        printf("\n");
    }
}
// Функция для вычисления обратной матрицы методом Гаусса-Жордана
double** inverse_matrix(int n, double **matrix, int *error) {
    *error = 0;
    
    // Создаем расширенную матрицу [A|I]
    double **augmented = memory_matrix(n, 2*n);
    double **inverse = memory_matrix(n, n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmented[i][j] = matrix[i][j];
            augmented[i][j+n] = (i == j) ? 1.0 : 0.0;
        }
    }

    // Прямой ход метода Гаусса
    for (int col = 0; col < n; col++) {
        // Поиск строки с максимальным элементом
        int max_row = col;
        for (int i = col + 1; i < n; i++) {
            if (fabs(augmented[i][col]) > fabs(augmented[max_row][col])) {
                max_row = i;
            }
        }

        // Проверка
        if (fabs(augmented[max_row][col]) < EPSILON) {
            *error = 1;
            free_matrix(n, augmented);
            free_matrix(n, inverse);
            return NULL;
        }

        // Перестановка строк
        if (max_row != col) {
            for (int j = 0; j < 2*n; j++) {
                double temp = augmented[col][j];
                augmented[col][j] = augmented[max_row][j];
                augmented[max_row][j] = temp;
            }
        }

        // Нормализация текущей строки
        double pivot = augmented[col][col];
        for (int j = 0; j < 2*n; j++) {
            augmented[col][j] /= pivot;
        }

        // Обнуление других строк
        for (int i = 0; i < n; i++) {
            if (i != col) {
                double factor = augmented[i][col];
                for (int j = 0; j < 2*n; j++) {
                    augmented[i][j] -= factor * augmented[col][j];
                }
            }
        }
    }

    // Извлечение обратной матрицы
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inverse[i][j] = augmented[i][j+n];
        }
    }
    
    free_matrix(n, augmented);
    return inverse;
}

// Функция для проверки результата (A * A^-1 = I) 
void verify_inverse(int n, double **A, double **A_inv) {
    double **product = memory_matrix(n, n);
    
    printf("\nПроверка результата (A * A⁻¹):\n");
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            product[i][j] = 0.0;
            for (int k = 0; k < n; k++) {
                product[i][j] += A[i][k] * A_inv[k][j];
            }
            // Округляем до 2 знаков для вывода
            printf("%8.0f ", fabs(product[i][j] - (i == j ? 1.0 : 0.0)) < EPSILON ? 
                  (i == j ? 1.0 : 0.0) : product[i][j]);
        }
        printf("\n");
    }
    
    free_matrix(n, product);
}

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