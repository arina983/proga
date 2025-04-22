#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "student.h"

int main() {
    struct Student students[N];
    srand(time(NULL));
    // Заполняем массив студентов случайными данными
    for (int i = 0; i < N; i ++) {
        char name[64];
        snprintf(name, sizeof(name), "Студент_%d", i + 1);
           int math = rand() % 101;
           int phy = rand() % 101;
           int inf = rand() % 101;
        students[i] = addStudent(name, math, phy, inf);
    }
    // Вывод информации о процессоре
    printf("Информация о процессоре:\n");
    system("grep -m 1 'model name' /proc/cpuinfo");
    system("grep -m 1 'cpu MHz' /proc/cpuinfo");

    // Замер времени для сортировки выбором
    clock_t start = clock();
    //selectSort(students, N);
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время работы сортировки выбором: %f секунд\n", time_spent);

    // Замер времени для сортировки подсчетом
    start = clock();
    //CountingSort(students, N);
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время работы сортировки подсчетом: %f секунд\n", time_spent);

    // Вывод размера данных
    printf("Размер данных: %lu байт\n", N * sizeof(struct Student));


    printf("до сортировки:\n");
    for (int i = 0; i < N; i ++){
        printStudentInfo(students[i]);
    }
     // Сортировка студентов по убыванию общего балла
     printf("после сортировки:\n");
     printf("Сортировка студентов по убыванию общего балла\n");
    CountingSort(students, N);

    
    selectSort(students, N);
    for(int i = 0; i < N; i ++){
        printStudentInfo(students[i]);
    }
    return 0;
}