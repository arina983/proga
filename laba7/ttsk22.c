#include <stdio.h>
void remove_str(char *txt, int *count) { // указатель для того, чтобы работать с исходным текстом, а не с его копией
    int i = 0;
    int j = 0; // для записи символов в новую строку
    *count = 0;
    for(i = 0; txt[i] != '\0'; i ++) { // проходит по тексту до тех пор, пока не встретит символ конца строки '\0'
        if (txt[i] != ' '){ // если символ не пробел, то копируем его 
        txt[j ++] = txt[i]; // cимвол из позиции i копируется в позицию j
        } else {
            (*count) += 1;
        }
    }    
    txt[j] = '\0'; // символ конца строки, чтобы строка корректно завершилась
}
   
int main(){
    char txt[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    int count = 0;
    remove_str(txt, &count);
    printf("%s\n", txt);
    printf("количество удаленнных пробелов: %d\n", count);
    return 0;
}