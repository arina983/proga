#include <stdio.h>
int main() { 
int a;
int i;
printf("Введите целое число a: ");
scanf("%d", &a);
printf("Биты c четными индексами: \n");
for(i=0; i<32; i+=2) {
    printf("%d", (a >> i) & 1 );

// 101 5
// 00000001
// 00000001
//&00000001

// 110
//011 011 001 001
}
printf("\nБиты с нечетными индексами: \n");
for(i=1; i<32; i+=2) {
printf("%d", (a >> i) & 1);
}
printf("\n");
return 0;

}