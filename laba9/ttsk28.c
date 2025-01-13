#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Для генерации случайных чисел

    void print_matrix(int n, int m, int **arr){
        for (int i = 0; i < n; i ++){
            for (int j = 0; j < m; j ++){
                printf("%d ", arr[i][j]);
            }
            printf("\n");
        }
    }
    void null(int n, int m, int **arr) {
        int count = 0;
        for (int i = 0; i < n; i ++) {
            for (int j = 0; j < m; j ++) {
                if (arr[i][j] == 0) {
                    count += 1;
                }
            } 
        }
        printf("Количество нулей в матрице: %d\n", count);
    }
    void average(int n, int m, int **arr){
        int sum = 0;
        for (int i = 0; i < n; i ++) {
            for (int j = 0; j < m; j ++) {
                sum += arr[i][j];
            }
        }
        double average  = sum / (n * m);
        printf("Среднее арифметическое элементов матрицы: %.2f\n", average);
    }
    void increasing(int n, int m, int **arr) {
        // создаем одномерный массив

        int size = n * m;
        int *flat = (int *)malloc(size * sizeof(int)); // выделяем память под ондомерный массив

        int index = 0; // индекс для заполнения массива flat

        // Копируем элементы матрицы в одномерный массив
        for (int i = 0; i < n; i ++) {
            for (int j = 0; j < m; j ++) {
                flat[index++] = arr[i][j];
            }
        }
        // Сортировка пузырьком одномерного массива
        for (int i = 0; i < size - 1; i ++) {
            for (int j = 0; j < size - i - 1; j ++) {
                if (flat[j] > flat[j + 1]) {
                    int tmp = flat[j];
                    flat[j] = flat[j + 1];
                    flat[j + 1] = tmp;
                }
            }
        }
        // Копируем отсортированные элементы обратно в матрицу
        index = 0;
        for (int i = 0; i < n; i ++) {
            for (int j = 0; j < n; j ++) {
                arr[i][j] = flat[index++];
            }
        }

        free(flat); // Освобождаем память
        printf("Упорядоченная по возрастанию матрица: \n");
        print_matrix(n, m, arr);

    }
    void swap_places(int n, int **arr) {
        for (int i = 0; i < n; i ++) {
            int tmp = arr[i][i]; // Элемент главной диагонали
            arr[i][i] = arr[i][n - 1 - i]; // Заменяем на элемент побочной диагонали
            arr[i][n - 1 - i] = tmp; // Заменяем элемент побочной диагонали
        }
        printf("Матрица после обмена главной и побочной диагоналей:\n");
        print_matrix(n, n, arr);
    }
    
int main() {
    int n;
    int m;
    printf("Введите количество строк: ");
    scanf("%d", &n);
    printf("Введите количество столбцов: ");
    scanf("%d", &m);

    // Динамическое выделение памяти для матрицы

    int **arr = (int **)malloc(n * sizeof(int *)); // Выделяем память для строк. (int **) — приведение типа, так как malloc возвращает указатель на void
    for (int i = 0; i < n; i ++) {
        arr[i] = (int *)malloc(m * sizeof(int)); // Выделяем память для столбцов
    }

    int o;
    printf("Введите способ заполнения элементов матрицы (1 - вручную, 2 - случайными числами): ");
    scanf("%d", &o);

    if (o == 1) {
        printf("Введите элементы матрицы: ");
        for (int i = 0; i < n; i ++) {
            for (int j = 0; j < m; j ++) {
                printf("[%d][%d] = ", i, j);
                scanf("%d", &arr[i][j] );
            }
        }
    } else if (o == 2) {
        srand(time(NULL)); // Инициализация генератора случайных чисел
        for (int i = 0; i < n; i ++){
            for (int j = 0; j < m; j ++){
                arr[i][j] = rand() % 100; // Случайные числа от 0 до 99
            }
        }
    } else {
        printf("Введите корректный способ заполнения");
        return 1;
    }

    printf("Mатрица: \n");
    print_matrix(n, m, arr);
    null(n, m, arr);
    average(n, m, arr);
    increasing(n, m, arr);

    if(n == m) {
        swap_places(n, arr);
    } else {
        printf("Невозможно выполнить обмен диагоналей: матрица не квадратная\n");
    }
    for (int i = 0; i < n; i ++) {
        free(arr[i]);  // Освобождаем память для каждой строки
    }
    free(arr); // Освобождаем память для массива указателей

    return 0;
}