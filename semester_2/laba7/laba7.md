Код реализует:
Создание и управление потоками;
Передачу параметров в потоки;
Обработку завершения потоков;
Реализацию алгоритма Sleepsort;

1. Создание потока
Реализация:

```c
pthread_t thread[4]; // Идентификаторы потоков
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

```c
void* thread_func(void* arg) {
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

```c
void thread_cleanup(void *arg) {
    int thread_id = ((info*)arg)->thread_id;
    printf("Поток %d: завершение работы\n", thread_id);
}
```
Использование pthread_cleanup_push/pop для регистрации функции очистки;
Вывод последовательности сообщений с задержкой;
Обработка параметров потока;

3. Управление потоками
Завершение потоков:

```c
sleep(2);
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

```c
void sleep_run() {
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

```c
int main() {
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

```c
#include <stdio.h>
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
```python 
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

![image](https://github.com/user-attachments/assets/8ae70849-3a14-4e21-95b7-26ce2c602368)


Код программы:
```c
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_SIZE 50
#define MAX_MATRIX_SIZE 5000

struct thread_inf {
    int thread_id;
    int message_count;
};

typedef struct thread_inf info;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int parent_turn = 1;

typedef struct {
    int thread_id;
    int N;
    int thread_count;
    int** A;
    int** B;
    int** C;
} MatrixThreadData;

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

void print_matrix(int N, int** matrix, const char* name) {
    printf("Матрица %s:\n", name);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void thread_cleanup(void *arg) {
    info* data = (info*)arg;
    printf("Поток %d: завершение работы\n", data->thread_id);
}

void* thread_func(void* arg) {
    pthread_cleanup_push(thread_cleanup, arg);

    info data = *(info*)arg;
    int thread_id = data.thread_id;
    int message_count = data.message_count;

    for (int i = 1; i <= message_count; i++) {
        pthread_mutex_lock(&mutex);
        while (parent_turn) {
            pthread_mutex_unlock(&mutex);
            usleep(100);
            pthread_mutex_lock(&mutex);
        }

        printf("Поток %d: Сообщение %d из %d\n", thread_id, i, message_count);
        parent_turn = 1;
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }

    printf("Поток %d завершен\n", data.thread_id);
    pthread_cleanup_pop(0);

    return NULL;
}

void* sleep_sort(void* arg) {
    int value = *(int*)arg;
    usleep(value * 1000);
    printf("%d ", value);
    fflush(stdout);
    return NULL;
}

void sleep_run() {
    int arr[MAX_SIZE];
    int n;
    pthread_t threads[MAX_SIZE];
    struct timespec start, end;
    double elapsed;

    printf("Введите количество элементов (не более %d): ", MAX_SIZE);
    scanf("%d", &n);
    if(n <= 0 || n > MAX_SIZE) {
        printf("Неккоректный размер массива\n");
        return;
    }

    printf("Введите %d неотрицательных чисел:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        if (arr[i] < 0) {
            printf("Отрицательные числа не поддерживаются\n");
            return;
        }
    }

    printf("Отсортированный массив: ");
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    for (int i = 0; i < n; i++) {
        if (pthread_create(&threads[i], NULL, sleep_sort, &arr[i]) != 0) {
            perror("Ошибка при создании потока");
            return;
        }
    }
    
    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed = (end.tv_sec - start.tv_sec) * 1000.0;
    elapsed += (end.tv_nsec - start.tv_nsec) / 1000000.0;
    
    printf("\nВремя сортировки: %.3f мс\n", elapsed);
}

int** allocate_matrix(int N) {
    int** matrix = (int**)malloc(N * sizeof(int*));
    if (matrix == NULL) {
        perror("Ошибка выделения памяти");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < N; i++) {
        matrix[i] = (int*)malloc(N * sizeof(int));
        if (matrix[i] == NULL) {
            perror("Ошибка выделения памяти");
            exit(EXIT_FAILURE);
        }
    }
    return matrix;
}

void free_matrix(int** matrix, int N) {
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int N, thread_count;
    struct timespec start_time, end_time;
    double elapsed_time;
    
    printf("Введите размер матрицы (не более %d): ", MAX_MATRIX_SIZE);
    scanf("%d", &N);
    
    printf("Введите число потоков для обработки матриц: ");
    scanf("%d", &thread_count);

    if (N <= 0 || N > MAX_MATRIX_SIZE || thread_count <= 0) {
        printf("Неккоректный размер\n");
        return 1;
    }

    // Выделение памяти для матриц
    int** A = allocate_matrix(N);
    int** B = allocate_matrix(N);
    int** C = allocate_matrix(N);

    // Инициализация матриц
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = 1;
            B[i][j] = 1;
            C[i][j] = 0;
        }
    }

    pthread_t threads[thread_count];
    MatrixThreadData thread_data[thread_count];

    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (int i = 0; i < thread_count; i++) {
        thread_data[i].thread_id = i;
        thread_data[i].N = N;
        thread_data[i].thread_count = thread_count;
        thread_data[i].A = A;
        thread_data[i].B = B;
        thread_data[i].C = C;
        
        if (pthread_create(&threads[i], NULL, matrix_multiply_thread, &thread_data[i]) != 0) {
            perror("Ошибка при создании потока");
            return 1;
        }
    }

    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);

    elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0;
    elapsed_time += (end_time.tv_nsec - start_time.tv_nsec) / 1000000.0;
    printf("Время умножения матриц: %.3f мс\n", elapsed_time);

    if (N < 5) {
        print_matrix(N, A, "A");
        print_matrix(N, B, "B");
        print_matrix(N, C, "C (result)");
    }

    // Освобождение памяти матриц
    free_matrix(A, N);
    free_matrix(B, N);
    free_matrix(C, N);

    // Часть 2: Взаимодействие потоков
    pthread_t thread[4];
    info thread_info_data[4];

    for (int i = 0; i < 4; i++) {
        thread_info_data[i].thread_id = i + 1;
        thread_info_data[i].message_count = 5;
    }

    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (int i = 0; i < 4; i++) {
        if (pthread_create(&thread[i], NULL, thread_func, &thread_info_data[i]) != 0) {
            perror("Ошибка при создании потока");
            return 1;
        }
    }

    for (int i = 1; i <= 5; i++) {
        pthread_mutex_lock(&mutex);
        while (!parent_turn) {
            pthread_mutex_unlock(&mutex);
            usleep(100);
            pthread_mutex_lock(&mutex);
        }

        printf("Родительский поток: строка %d\n", i);
        parent_turn = 0;
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }

    sleep(2);
    for (int i = 0; i < 4; i++) {
        pthread_cancel(thread[i]);
    }
    for (int i = 0; i < 4; i++) {
        pthread_join(thread[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);

    elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0;
    elapsed_time += (end_time.tv_nsec - start_time.tv_nsec) / 1000000.0;
    printf("Время связи с потоком: %.3f мс\n", elapsed_time);

    pthread_mutex_destroy(&mutex);

    // Часть 3: Sleepsort
    sleep_run();

    return 0;
}

```
