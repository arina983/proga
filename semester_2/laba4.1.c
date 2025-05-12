#include <stdio.h>
#include <stdlib.h>

int main() {
    // Указываем путь к файлу
    const char *file_path = "/home/arina/proga.txt";

    // Открываем файл для чтения и записи
    FILE *file = fopen(file_path, "r+");
    if (file == NULL) {
        printf("Ошибка: не удалось открыть файл %s\n", file_path);
        return 1; // Завершаем программу с кодом ошибки
    }

    int count = 0; 
    char ch;

    // Читаем файл посимвольно
    while ((ch = fgetc(file)) != EOF) {
        // Проверяем, является ли символ цифрой
        if (ch >= '0' && ch <= '9') {
            count++; 
        }
    }

    // Если произошла ошибка при чтении файла
    if (ferror(file)) {
        printf("Ошибка при чтении файла\n");
        fclose(file); 
        return 1; 
    }

    // Добавляем количество цифр в конец файла
    fprintf(file, "\nКоличество цифр в файле: %d\n", count);

    // Если произошла ошибка при записи в файл
    if (ferror(file)) {
        printf("Ошибка при записи в файл\n");
        fclose(file); 
        return 1; 
    }

    fclose(file);

    printf("Программа успешно завершена. Количество цифр: %d\n", count);
    return 0;
}
