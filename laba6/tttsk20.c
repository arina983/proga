#include <stdio.h>
int main() {
    int A[] = {1, 2, 3, 4, 5, 6};
    int B[] = {2, -4, 6, 8, 10, 1};
    int C[6];
    int n = 3;
    // Если есть n комплексных чисел, то массив будет содержать 2 * n элементов (по два на каждое комплексное число)
    printf("Результат сложения массивов А и В: \n");
    for (int i = 0; i < n * 2; i += 2) { 
        C[i] = A[i] + B[i]; //
        C[i + 1] = A[i + 1] + B[i + 1]; //
        printf("C[%d] = %d + %di\n", i / 2, C[i], C[i + 1]);
    }
    printf("Максимальная реальная часть комплексных чисел массива А: \n");
    int max = A[0];
    for (int k = 0; k < n * 2; k += 2) {
        if (A[k] > max){
            max = A[k];
        }
    }
    printf("%d\n", max);

    printf("Количество мнимых частей < 0 в массиве В:\n");
    int count = 0;
    for (int l = 1; l < n * 2; l += 2){
        if (B[l] < 0){
           count += 1;
        }
    }
    printf("%d\n", count);

    printf("Среднее арифметическое элементов массива C:\n");
    int sum = 0;
    for (int j = 0; j < n * 2; j ++) {
        sum += C[j];
    }
    int avarage = sum / (n * 2);
    printf("%d\n", avarage);
return 0;
}
