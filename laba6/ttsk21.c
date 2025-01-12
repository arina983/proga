#include <stdio.h>
int main() {
    int n;
    printf("Введите количество элементов массива X: ");
    scanf("%d", &n);

    int X[n];
    
    printf("Заполните массив числами:\n");
    for (int i = 0; i < n; i++) {
        printf("X[%d] = ", i);
        scanf("%d", &X[i]);
    }
    printf("Массив Х: {");
    for (int i = 0; i < n; i++){
        printf("%d", X[i]);
        if (i < n - 1) { // если элемент не последний то разделяем запятой
            printf(", ");
        }
    }
    printf("}\n");
    int Y[n]; // создаем массив Y, в котором будут храниться все нечетные элементы массива X
    int y = 0;
    for (int i = 1; i < n; i += 2){
        Y[y] = X[i];
        y ++;
    }
    printf("Массив Y: {");
    for (int i = 0; i < y; i ++) {
        printf("%d", Y[i]);
        if (i < y - 1) {
            printf(", ");
        }
    }
    printf("}\n");

    printf("Количество простых чисел в массиве Х: ");
    int count_x = 0; 
    for (int i = 0; i < n; i ++){
        int num = X[i];
        if (num < 2) { // числа меньше 2 не являются простыми 
            continue;
        }
        int is_prime_x = 1;
        // делители до квадратного корня числа (j * j <= num).
        for (int j = 2; j * j <= num; j++) {
            if (num % j == 0) {
                is_prime_x = 0;
                break;
            }
        } 
        
        if (is_prime_x) {
            count_x += 1;
        } 
    }  
    printf("%d\n", count_x);
    printf("Количество простых чисел в массиве Y: ");
    int count_y = 0;
    for (int i = 0; i < y; i ++) {
        int num = Y[i];
        if (num < 2){
            continue;
        }
        int is_prime_y = 1;
        for (int j = 2; j * j <= num; j ++) {
            if (num % j == 0) {
                is_prime_y = 0;
                break;
            }
        }
        if (is_prime_y) {
            count_y += 1;
        }
    }
    
    printf("%d\n", count_y);
    printf("Среднее арифметическое массивов: ");
    double sum = 0;
    for (int i = 0; i < n; i ++){
        sum += X[i]; // суммируем элементы массива Х
    }
    for (int i = 0; i < y; i ++) {
        sum += Y[i]; // суммируем элементы массивa Y
    }
    double avarage = sum / (n + y);
    printf("%.2lf\n", avarage);
    return 0;
}