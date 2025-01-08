#include <stdio.h>
int main() {
int n1;
int n2;
printf("Введите два числа: ");
scanf("%d %d", &n1, &n2);
int i = n1;
for (; !(n1 % i == 0 && n2 % i == 0); i--);{
    printf("НОД: %d\n", i);
}
return 0;    
}