#include <stdio.h>
int main() {
    int a;
    int k;
    printf("Введите целое число а: ");
    scanf("%d", &a);
    printf("Введите количество позиций k: ");
    scanf("%d", &k);
    int bits = sizeof(int) * 8;
    k = k % bits;
    for (int i = 0; i < k; i ++) {
        int first_bits = (a >> (bits - 1)) & 1;
        a = a << 1;
        // Если старший бит был 1, устанавливаем младший бит в 1
        if (first_bits){
            a = a | 1; 
        }
    }
    printf("Результат: %d\n", a);
    return 0;
}