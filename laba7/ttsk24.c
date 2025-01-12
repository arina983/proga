#include <stdio.h>

void remove_c(char *txt){
    int i = 0;
    int j = 0;
    for (i = 0; txt[i] != '\0'; i ++){
        if(txt[i] != ','){ // если символ не запятая то копируем его
            txt [j++] = txt[i];
        }
    }
    txt[j] = '\0'; // завершаем строку для корректного вывода
    }


int main() {
    char txt[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    remove_c(txt);
    printf("%s\n", txt);

    return 0;
}