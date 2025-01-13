#include <stdio.h> 
#include <stdlib.h>

    void print_matrix(int n, int m, int arr[n][m]){
        for (int i = 0; i < n; i ++){
            for (int j = 0; j < m; j ++){
                printf("%d ", arr[i][j]);
            }
            printf("\n");
        }
    }
    void null(int n, int arr[n][n]) {
        int count = 0;
        for (int i = 0; i < n; i ++) {
            for (int j = 0; j < n; j ++) {
                if (arr[i][j] == 0) {
                    count += 1;
                }
            } 
        }
        printf("Количество нулей в матрице: %d\n", count);
    }
    void average(int n, int arr[n][n]){
        int sum = 0;
        for (int i = 0; i < n; i ++) {
            for (int j = 0; j < n; j ++) {
                sum += arr[i][j];
            }
        }
        double average  = sum / (n * n);
        printf("Среднее арифметическое элементов матрицы: %.2f\n", average);
    }
    void increasing(int n, int arr[n][n]) {
        // создаем одномерный массив
        int size = n * n;
        int flat[size];
        int index = 0; // индекс для заполнения массива flat

        // Копируем элементы матрицы в одномерный массив
        for (int i = 0; i < n; i ++) {
            for (int j = 0; j < n; j ++) {
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
        printf("Упорядоченная по возрастанию матрица: \n");
        print_matrix(n, n, arr);
    }
    void swap_places(int n, int arr[n][n]) {
        for (int i = 0; i < n; i ++) {
            int tmp = arr[i][i]; // Элемент главной диагонали
            arr[i][i] = arr[i][n - 1 - i]; // Заменяем на элемент побочной диагонали
            arr[i][n - 1 - i] = tmp; // Заменяем элемент побочной диагонали
        }
        printf("Матрица после обмена главное и побочной диагоналей:\n");
        print_matrix(n, n, arr);
    }
    
int main() {
    int n;
    printf("Введите размер матрицы: ");
    scanf("%d", &n);
    int o;
    printf("Введите способ заполнения элементов матрицы (1 - вручную, 2 - случайными числами): ");
    scanf("%d", &o);
    int arr[n][n];
    if (o == 1) {
        printf("Введите элементы матрицы: ");
        for (int i = 0; i < n; i ++) {
            for (int j = 0; j < n; j ++) {
                printf("[%d][%d] = ", i, j);
                scanf("%d", &arr[i][j] );
            }
        }
    } else if (o == 2) {
        for (int i = 0; i < n; i ++){
            for (int j = 0; j < n; j ++){
                arr[i][j] = rand() % 100;
            }
        }
    } else {
        printf("Введите корректный способ заполнения");
        return 1;
    }
    printf("Mатрица: \n");
    print_matrix(n, n, arr);
    null(n, arr);
    average(n, arr);
    increasing(n, arr);
    swap_places(n, arr);

    return 0;
}