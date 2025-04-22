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
