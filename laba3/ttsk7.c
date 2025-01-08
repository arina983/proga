#include <stdio.h>
int main() {
    int a, b;
    printf("Введите числa: ");
    scanf("%d %d", &a, &b);
    int n = a;
    for(; n%a!=0 || n%b!=0; n ++); {
       printf("Наименьшее общее кратное: %d\n", n);
    }
    return 0;
}