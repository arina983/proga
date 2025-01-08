#include <stdio.h>
int main() {
    int s = 0;
    int a;
    printf("Введите число: ");
    scanf("%d", &a);
    for(int n = 2; n < a; n ++)
    if(a % n == 0){
         s ++;
        }
    
    if(s == 0) {
        puts("1"); // простое число
    }
    else {
        puts("0"); // не простое число
    }
    

}