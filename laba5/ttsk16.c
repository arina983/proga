#include <stdio.h>
int main() {
    int a;
    printf("Введите целое число: ");
    scanf("%d", &a);
    // вывод битов с четными индексами
    printf("Четные индексы: ");
    for (int i = 0; i < sizeof(int) * 8; i += 2){
        int bit = (a >> i) & 1; // получаем бит на позиции i
        printf("%d", bit);
    }
    printf("\n");
    // вывод битов с нечетными индексами
    printf("Нечетные индексы: ");
    for (int j = 1; j < sizeof(int) * 8; j += 2) {
        int bit = (a >> j) & 1; // получаем бит на позиции j
        printf("%d", bit);
    }
    printf("\n");
    return 0;
}