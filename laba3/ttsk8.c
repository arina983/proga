#include <stdio.h>
int main() {
    int n = 2;
    int a;
    printf("Введите число: ");
    scanf("%d", &a);
    for(; n < a; n++) {
        if (a % n == 0){
            break;
        }
    }
        if(n == a) {
            puts("1");
    } else 
        puts("0");
return 0;
}