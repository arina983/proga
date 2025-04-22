#include <stdlib.h>
#include "student.h"

// Функция для сортировки студентов по убыванию общего балла (сортировка выбором)
void selectSort(struct Student students[], int n){
    for (int i = 0; i < n; i ++){
        int k = i;
    for (int j = i + 1; j < n; j ++) {
        if (students[j].total > students[k].total){ // Сравниваем по первому общему баллу
            k = j; 
        }
    }
    //Устраняем фиктивные перестановки
    if (k != i) {
    // Меняем местами студентов
    struct Student temp = students[i];
    students[i] = students[k];
    students[k] = temp;
        }
    }   
}
// сортировка подсчетом
void CountingSort(struct Student students[], int n){
    int max_score= 0;
    for (int i = 0; i < n; i ++){
        if(students[i].total > max_score){
            max_score = students[i].total;
        }
    } 
    // Создаем массив для подсчета
    int *count = (int *)malloc((max_score + 1) * sizeof(int));
    for (int i = 0; i <= max_score; i++) {
        count[i] = 0;
    }
     // Подсчитываем количество студентов для каждого выставленного балла
    for (int i = 0; i < n; i++) {
        count[students[i].total]++;
    }
     // Создаем массив для хранения отсортированных студентов
    struct Student *output = (struct Student *)malloc(n * sizeof(struct Student));

    int index = 0;
    for (int i = max_score; i >= 0; i--) {
        while (count[i] > 0) {
            for (int j = 0; j < n; j++) {
                if (students[j].total == i) {
                    output[index] = students[j];
                    index++;
                    count[i]--;
                    if(count[i] == 0) break; // если мы уже добавили всех студентов с этим баллом, выходим.
                    break;
                }
            }
        }
    }
         // Копируем отсортированный массив обратно в students
    for (int i = 0; i < n; i++) {
        students[i] = output[i];
    }  
    // Освобождаем выделенную память
    free(count);
    free(output);
} 
     
