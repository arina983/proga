#include <stdio.h>
#include "function.h"

int main(){

    int n;

    printf("Введите количество людей: ");
    scanf("%d", &n);

    struct date birth[n];
    for(int i = 0; i < n; i++ ){
        printf("Введите день рождения: %d\n", i + 1 );
        scanf("%d", &birth[i].day);
        printf("Введите месяц рождения:\n");
        scanf("%d", &birth[i].month);
        printf("Введите год рождения: \n");
        scanf("%d", &birth[i].year);
    }
    for(int i =0; i < n; i ++){
        printf("Человек %d родился в: ", i + 1);
        decade(birth[i].day);
        season(birth[i].month);
        century(birth[i].year);
    }
   

return 0;
}



