#include <stdio.h>
int main() {
    int a;
    int s = 0;
    printf("Введите число: ");
    scanf("%d", &a);
    for (int n = 2; n < a; n ++){
    if (a % n == 0){
         s = 1; 
         break; 
         }
    }
    printf("%d\n", s);
}
// если число простое, выводится '0', если не простое, то '1' 