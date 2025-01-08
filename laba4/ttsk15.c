#include <stdio.h>
int main() {
    int n;
    printf("Введите размер: ");
    scanf("%d", &n);
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j ++){
            if(j >= i){
                printf(" o");
            } else {
                printf(" ");
            }
        } 
        printf("\n");
    }
    for(int i = 1; i < n; i ++){
        for(int j = 0; j < n; j ++){
            if(j >= n - i - 1){
                printf(" o");
            } else {
                printf(" ");
            }   
        }
        printf("\n");    
    }

return 0;    
}