#include <stdio.h>

int main() {
    char text[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    int has_digits = 0;
    int sum_digits = 0;
    
//цикл для обнаружения и подсчета суммы цифр

    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= '0' && text[i] <= '9') { // Проверка на цифру
            has_digits = 1;
            sum_digits += text[i] - '0'; // Преобразование символа в число
        } 
    }

    if (has_digits) {
        printf("В предложении есть цифры. Их сумма: %d\n", sum_digits);
    } else {
        printf("В предложении нет цифр.\n");
    }
    return 0;
}