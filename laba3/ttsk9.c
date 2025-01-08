#include <stdio.h>
int main() {
    int a;
    int n = 2;
    printf("Введите число: ");
    scanf("%d", &a);
    for(; n < a && a % n!= 0; n ++) {}
        if(n == a){ 
        puts("1"); // число простое
    } else {
        puts("0"); // число не простое
    }
    
return 0;    
}