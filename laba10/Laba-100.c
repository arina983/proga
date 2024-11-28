#include <stdio.h>

struct date {
    int day;
    int month;
    int year;
};

void decade (int day){
    if (day >= 1 && day <= 10)
    printf("1 декада\n");
    if (day >= 11 && day <= 20)
    printf("2 декада\n");
    else
    printf("3 декада\n");
}
void season (int month){
    if (month ==12 || month == 1 || month == 2)
    printf("Зима\n");
    if (month >= 3 && month <= 5)
    printf("Весна\n");
    if (month >= 6 && month <= 8)
    printf("Лето\n");
    if (month >= 9 && month <= 11)
    printf("Осень\n");
}

void century (int year) {
    int century = (year + 99) / 100;
    printf("%d век\n", century);
    }

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
