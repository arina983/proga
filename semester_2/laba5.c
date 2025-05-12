#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Route {
    char start[50];
    char finish[50];
    int route_number;
};

int main(int argc, char *argv[]){

    if (argc != 2) {
        printf("Ошибка: %s не введено имя файла\n", argv[0]);
        return 1;
    }


    FILE *file = fopen(argv[1], "wb"); 
    if (file == NULL) {
        perror("Ошибка создания файла");
        return 1;
    }

    struct Route routes[] = {
        {"Москва", "Санкт-Петербург", 101},
        {"Новосибирск", "Омск", 202},
        {"Казань", "Екатеринбург", 303}
    };

    fwrite(routes, sizeof(struct Route), 3, file);
    fclose(file);

    FILE *file_read = fopen("Spravka.dat", "rb");
    if (file == NULL){
        perror("Ошибка в чтении файла");
        return 1;
    }
    
    struct Route route;
    int n;
    int found = 0;
    
    printf("Введите номер маршрута для поиска: \n");
    scanf("%d", &n);

    while (fread(&route, sizeof(struct Route), 1, file_read)) {
        if(route.route_number == n){
            printf("Маршрут найден:\n");
            printf("Начальный пункт: %s\n", route.start);
            printf("Конечный пункт: %s\n", route.finish);
            printf("Номер маршрута: %d\n", route.route_number);
            found = 1;
            break;
        }
    }
    if(!found){
        printf("Информация о маршруте %d отсутствует\n", n);
    }

    
    fclose(file_read);

    return 0;
}
