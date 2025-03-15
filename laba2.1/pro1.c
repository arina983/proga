#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 10
struct Student {
    char name[64];
    int math;
    int phy;
    int inf;
    int total;
};

struct Student addStudent(char name[], int math, int phy, int inf) {
    struct Student newStudent;
    strcpy(newStudent.name, name); //копируем имя студента
        newStudent.math = math;
        newStudent.phy = phy;
        newStudent.inf = inf;
        newStudent.total = math + phy + inf;
    return newStudent;
}
void printStudentInfo(struct Student student){
    printf("Имя стyдента: %s\n", student.name);
    printf("Балл по математике: %d, Балл по физике: %d,Балл по информатике: %d, Общий бал: %d", student.math, student.phy, student.inf, student.total);
    printf("\n");
}
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