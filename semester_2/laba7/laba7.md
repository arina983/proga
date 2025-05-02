Код реализует:
Создание и управление потоками;
Передачу параметров в потоки;
Обработку завершения потоков;
Реализацию алгоритма Sleepsort;

1. Создание потока
Реализация:

```pthread_t thread[4]; // Идентификаторы потоков
info thread_data[4]; // Данные потоков

for (int i = 0; i < 4; i++) {
    thread_data[i].thread_id = i + 1;
    thread_data[i].message_count = 5;
}

for (int i = 0; i < 4; i++) {
    int result = pthread_create(&thread[i], NULL, thread_func, &thread_data[i]);
    if (result != 0) {
        perror("Ошибка при создании потока");
        return 1;
    }
}
```
Создано 4 потока с помощью pthread_create();
Каждый поток получает уникальные параметры через структуру thread_inf;
Обработка ошибок создания потоков;

2. Функция потока
Реализация:

```void* thread_func(void* arg) {
    pthread_cleanup_push(thread_cleanup, arg);
    
    info data = *(info*)arg;
    for (int i = 1; i <= data.message_count; i++) {
        printf("Поток %d: Сообщение %d из %d\n", data.thread_id, i, data.message_count);
        sleep(1);
    }
    
    pthread_cleanup_pop(0);
    return NULL;
}
```
Функция очистки:

```void thread_cleanup(void *arg) {
    int thread_id = ((info*)arg)->thread_id;
    printf("Поток %d: завершение работы\n", thread_id);
}
```
Использование pthread_cleanup_push/pop для регистрации функции очистки;
Вывод последовательности сообщений с задержкой;
Обработка параметров потока;

3. Управление потоками
Завершение потоков:

```sleep(2);
for (int i = 0; i < 4; i++) {
    pthread_cancel(thread[i]); // Принудительная отмена
}

for (int i = 0; i < 4; i++) {
    pthread_join(thread[i], NULL); // Ожидание завершения
}
```
Потоки принудительно завершаются через 2 секунды;
Использование pthread_join для ожидания завершения;
Функция очистки вызывается при отмене потока;

4. Sleepsort реализация
Функция сортировки:

```void* sleep_sort(void* arg) {
    int value = *(int*)arg;
    usleep(value * 1000);
    printf("%d ", value);
    fflush(stdout);
    return NULL;
}
```
Инициализация и запуск:

```void sleep_run() {
    int arr[MAX_SIZE];
    int n;
    pthread_t threads[MAX_SIZE];

    // Ввод данных
    printf("Введите количество элементов(Не более %d)\n", MAX_SIZE);
    scanf("%d", &n);

    // Проверка ввода
    if(n <= 0 || n > MAX_SIZE) {
        printf("Некорректный размер массива\n");
        return;
    }

    printf("Введите %d неотрицательных чисел\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        if (arr[i] < 0) {
            printf("Отрицательные числа не поддерживаются");
            return;
        }
    }

    // Сортировка
    printf("Отсортированный массив ");
    for (int i = 0; i < n; i++) {
        pthread_create(&threads[i], NULL, sleep_sort, &arr[i]);
    }

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("\n");
}
```
Каждый элемент массива обрабатывается в отдельном потоке;
Использование usleep для задержки, пропорциональной значению элемента;
Проверка входных данных;
Ограничение на размер массива (MAX_SIZE = 50);

5. Главная функция
Реализация:

```int main() {
    // Создание и управление потоками (см. выше)
    
    // Вывод из основного потока
    for (int i = 1; i <= 5; i++) {
        printf("Родительский поток: строка %d\n", i);
        sleep(1);
    }
    
    // Запуск Sleepsort
    sleep_run();

    return 0;
}
```
Готовый код:

```#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define MAX_SIZE 50

struct thread_inf {
    int thread_id; // идентификатор потока
    int message_count; // кол-во собщений для вывода
};

typedef struct thread_inf info;

void thread_cleanup(void *arg){
    int thread_id = ((info*)arg)->thread_id;
    printf("Поток %d: завершение работы\n", thread_id);
}

void* thread_func(void* arg) {

      pthread_cleanup_push(thread_cleanup, arg); //(5)
    
    // Получаем данные потока из аргументов
    info data = *(info*)arg;

    // вывод сообщений
    for (int i = 1; i <= data.message_count; i ++){
        printf("Поток %d: Сообщение %d из %d\n", data.thread_id, i, data.message_count);
        sleep(1);
    }
    printf("Поток %d\n", data.thread_id);
    pthread_cleanup_pop(0); // удаляем функцию очистки 

    return NULL;
}

//Sleepsort
void* sleep_sort(void* arg) {
    int value = *(int*)arg;
    usleep(value * 1000);
    printf("%d ", value);
    fflush(stdout);
    return NULL;
}

void sleep_run(){

    int arr[MAX_SIZE];
    int n;
    pthread_t threads[MAX_SIZE]; // Массив идентификаторов потоков

    printf("Введите количество элементов(Не более %d)\n", MAX_SIZE);
    scanf("%d", &n);

    if(n <= 0 || n > MAX_SIZE){
        printf("Некорректный размер массива\n");
        return;
    }

    printf("Введите %d неотрицательных чисел\n", n);
    for (int i = 0; i < n; i ++){
        scanf("%d", &arr[i]);
        if (arr[i] < 0){
            printf("Отрицательные числа не поддерживаются");
            return;
        }
    }

    // Создание потоков для сортировки
    printf("Отсортированный массив ");
    for (int i = 0; i < n; i++) {
        pthread_create(&threads[i], NULL, sleep_sort, &arr[i]);
    }
    // Ожидание завершения всех потоков
    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("\n");
}

int main(){
    pthread_t thread[4]; //идентификаторы потока
    info thread_data[4]; //данные потока

    for (int i = 0; i < 4; i ++){
        thread_data[i].thread_id = i + 1;
        thread_data[i].message_count = 5;
    }

    for (int i = 0; i < 4; i ++){
        int result = pthread_create(&thread[i], NULL, thread_func, &thread_data[i]);
        if (result != 0){
            perror("Ошибка при создании потока");
            return 1;
        }
    }

    sleep(2);
    for (int i = 0; i < 4; i++) {
        pthread_cancel(thread[i]);  // Принудительная отмена (4 задание)
    }

    for (int i = 0; i < 4; i ++){
        pthread_join(thread[i], NULL); // завершение потоков
    }

    for (int i = 1; i <= 5; i ++){
        printf("Родительский поток: строка %d\n", i);
        sleep(1);
    }
    
    sleep_run();

    return 0;
}
```
---Выводы---
Программа успешно демонстрирует:

Создание и управление несколькими потоками;
Безопасную передачу параметров в потоки;
Корректное завершение потоков с обработкой очистки;
Реализацию нестандартного алгоритма сортировки с использованием потоков;

Демонстрация работы:

![Снимок экрана 2025-04-22 144045](https://github.com/user-attachments/assets/0e5df96b-5f9c-477b-b3d0-d4c90bdc5009)
Далее было реализовано: 
Синхронизированный вывод

Модифицирована программа так, чтобы вывод родительского и дочернего потока был синхронизован: сначала родительский поток выводить первую строку, затем дочерний, затем родительский вторую строку и т.д. Использован mutex. 
![image](https://github.com/user-attachments/assets/1f1cacd3-6535-42b4-a4e2-dc057650ccfa)

Перемножение квадратных матриц NxN

a.	Написана функцию произведения двух квадратных матриц A и B размером NxN (на выходе получим матрицу C). Исходные матрицы A и B заполнены единицами в основном потоке с функцией main.
![image](https://github.com/user-attachments/assets/b8e2b6b4-4e82-413b-b990-197fe054760d)

b.	С командной строки считыввется размер матрицы и количество потоков. Распараллеливается перемножение матриц разбая матрицу на равные части между потоками в главной функции по следующему принципу: N / threads
![image](https://github.com/user-attachments/assets/8dc8c739-6c41-4570-af99-bac7dda5338d)

Время выполнения

Замерено время выполнения с момента создания потоков (до цикла с pthread_create) и до завершения работы потоков (после цикла pthread_join). Исходя из результатов построен график на Python
```
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from matplotlib.ticker import ScalarFormatter

# Your data
data = {
    "Threads": [1, 1, 1, 1, 1, 8, 8, 8, 8, 8, 32, 32, 32, 32, 32, 64, 64, 64, 64, 64, 128, 128, 128, 128, 128],
    "Matrix_Size": [100, 600, 1100, 1600, 2100, 100, 600, 1100, 1600, 2100, 100, 600, 1100, 1600, 2100, 100, 600, 1100, 1600, 2100, 100, 600, 1100, 1600, 2100],
    "Time_ms": [11.256, 2572.287, 14430.957, 49242.526, 194598.707, 4.807, 483.789, 2825.489, 11600.448, 39271.788, 6.660, 468.196, 2342.818, 9865.757, 34885.378, 15.533, 471.779, 2863.454, 11652.397, 42385.869, 42.112, 689.024, 3869.364, 12315.637, 41202.034]
}

df = pd.DataFrame(data)

# Setting the style
plt.style.use('seaborn-v0_8-whitegrid')
plt.rcParams['figure.figsize'] = [12, 7]
plt.rcParams['font.size'] = 12

# Creating the figure
fig, ax = plt.subplots()

# Unique thread counts and color map
threads = sorted(df['Threads'].unique())
colors = plt.cm.plasma(np.linspace(0.1, 0.9, len(threads)))

# Plotting for each thread count
for i, thread_count in enumerate(threads):
    subset = df[df['Threads'] == thread_count].sort_values('Matrix_Size')
    ax.plot(subset['Matrix_Size'], subset['Time_ms'], 
            marker='o', 
            linestyle='-', 
            linewidth=2,
            markersize=8,
            color=colors[i],
            label=f'{thread_count} потоков')

# Axis settings
ax.set_xscale('linear')
ax.set_yscale('log')
ax.set_xlim(50, 2200)
ax.set_ylim(1, 3e5)

# Formatting axes
ax.xaxis.set_major_formatter(ScalarFormatter())
ax.yaxis.set_major_formatter(ScalarFormatter())
ax.set_yticks([10, 100, 1000, 10000, 100000])

# Labels
ax.set_xlabel('Размер матрицы', fontsize=12, labelpad=10)
ax.set_ylabel('Время выполнения (мкс)', fontsize=12, labelpad=10)
ax.set_title('Зависимость времени выполнения от размера матрицы и количества потоков', fontsize=14, pad=20)

# Grid
ax.grid(True, which='both', linestyle='--', alpha=0.5)

# Legend
legend = ax.legend(title='Количество потоков',
                 bbox_to_anchor=(1.02, 1),
                 loc='upper left',
                 frameon=True,
                 framealpha=0.9)

plt.tight_layout()
plt.show()
```

![image](https://github.com/user-attachments/assets/dd6be6f2-d247-4394-84fc-d8b402607b2d)

Код программы:
```
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define MAX_THREADS 128
#define MAX_MATRIX_SIZE 2500

typedef struct {
    int thread_id;
    int N;
    int thread_count;
    int** A;
    int** B;
    int** C;
} MatrixThreadData;

int** allocate_matrix(int N) {
    int** matrix = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        matrix[i] = (int*)malloc(N * sizeof(int));
    }
    return matrix;
}

void free_matrix(int** matrix, int N) {
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void initialize_matrix(int N, int** matrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 100;
        }
    }
}

void* matrix_multiply_thread(void* arg) {
    MatrixThreadData* data = (MatrixThreadData*)arg;
    int rows_per_thread = data->N / data->thread_count;
    int start_row = data->thread_id * rows_per_thread;
    int end_row = (data->thread_id == data->thread_count - 1) ? data->N : start_row + rows_per_thread;

    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < data->N; j++) {
            data->C[i][j] = 0;
            for (int k = 0; k < data->N; k++) {
                data->C[i][j] += data->A[i][k] * data->B[k][j];
            }
        }
    }
    return NULL;
}

void benchmark_matrix_multiplication(int N, int thread_count, FILE* output_file) {
    int** A = allocate_matrix(N);
    int** B = allocate_matrix(N);
    int** C = allocate_matrix(N);
    
    initialize_matrix(N, A);
    initialize_matrix(N, B);
    
    pthread_t threads[MAX_THREADS];
    MatrixThreadData thread_data[MAX_THREADS];
    
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (int i = 0; i < thread_count; i++) {
        thread_data[i].thread_id = i;
        thread_data[i].N = N;
        thread_data[i].thread_count = thread_count;
        thread_data[i].A = A;
        thread_data[i].B = B;
        thread_data[i].C = C;
        
        pthread_create(&threads[i], NULL, matrix_multiply_thread, &thread_data[i]);
    }

    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);

    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0 + 
                         (end_time.tv_nsec - start_time.tv_nsec) / 1000000.0;
    
    fprintf(output_file, "%d,%d,%.3f\n", N, thread_count, elapsed_time);
    printf("N=%d, Threads=%d, Time=%.3f ms\n", N, thread_count, elapsed_time);
    
    free_matrix(A, N);
    free_matrix(B, N);
    free_matrix(C, N);
}

int main() {
    srand(time(NULL));
    
    // Исправленный путь к файлу (Linux-style для WSL)
    FILE* output_file = fopen("/home/arina/matrix_benchmark_results.csv", "w");
    if (output_file == NULL) {
        perror("Не удалось открыть файл для записи результатов");
        return 1;
    }
    fprintf(output_file, "MatrixSize,ThreadCount,TimeMs\n");
    
    // Тестируем различные размеры матриц и количество потоков
    int matrix_sizes[] = {100, 250, 500, 750, 1000, 1250, 1500, 1750, 2000, 2250, 2500};
    int thread_counts[] = {1, 2, 4, 8, 16, 32, 64, 128};
    
    for (int i = 0; i < sizeof(matrix_sizes)/sizeof(matrix_sizes[0]); i++) {
        for (int j = 0; j < sizeof(thread_counts)/sizeof(thread_counts[0]); j++) {
            benchmark_matrix_multiplication(matrix_sizes[i], thread_counts[j], output_file);
        }
    }
    
    fclose(output_file);
    printf("Тестирование завершено. Результаты сохранены в /home/arina/matrix_benchmark_results.csv\n");
    
    return 0;
}
```
