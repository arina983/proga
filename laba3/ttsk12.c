#include <stdio.h>
int main() {
    int n;
    int s = 1;
    printf("Введите число: ");
    scanf("%d", &n);
    for( int i = 1; i <= n; i ++ ){
    s = s * i;
    }
    printf("Результат: %d\n", s);

}
// вычисляет факториал числа