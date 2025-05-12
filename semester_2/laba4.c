#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_word 30

// для нахождения самого длинного слова в строке 
void replace_ARINA(char *line) {
    char longest_word[max_word] = "";
    char word[max_word];
    int max_length = 0; // самое длинное слово
    int word_length = 0; // текущее слово 
    int i = 0;

while (line[i] != '\0'){
    if (line[i] != ' ' && line[i] != '\n'){
        word[word_length++] = line[i];
    } else {
        word[word_length] = '\0';
        if (word_length > max_length){
            max_length = word_length;
            strcpy(longest_word, word);
        }
        word_length = 0;
    }
    i ++;
}
    // Проверяем последнее слово в строке
    word[word_length] = '\0';
    if (word_length > max_length) {
        strcpy(longest_word, word);
    }

    // Заменяем самое длинное слово на "ARINA"
    if (max_length > 0) {
        char *pos = strstr(line, longest_word); // ищет позицию самого длинного слова в строке.
        if (pos != NULL) {
            strncpy(pos, "ARINA", 5);
            pos[5] = ' '; // Добавляем пробел после замены
        }
    }
}

int main(int argc, char *argv[]){
    if (argc != 2) {
        fprintf(stderr, "Ошибка при запуске %s: мало аргументов \n", argv[0]);
        exit(1);
}
FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        perror("Ошибка при открытии файла");
        exit(1);
    }
FILE *temp_file = fopen("/home/arina/proga_temp.txt", "w");
    if (temp_file == NULL) {
        perror("Ошибка при открытии файла");
        fclose(input_file);
        exit(1);
    }
    
    char line[1024];
    while (fgets(line, sizeof(line), input_file)) {
        replace_ARINA(line);
        fprintf(temp_file, "%s", line);
    }

    fclose(input_file);
    fclose(temp_file);

    // Удаляем оригинальный файл и переименовываем временный файл
    remove(argv[1]);
    rename("/home/arina/proga_temp.txt", argv[1]);

    printf("Программа завершена успешно. Файл '/home/arina/proga.txt' изменен.\n");

    return 0;
}
