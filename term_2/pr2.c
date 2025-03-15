#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>  // Для функции toupper()

struct node {
    int data;
    struct node *next;  // Указатель на следующий узел
    struct node *prev; // Указатель на предыдущий узел
};

typedef struct node node_t;

// Функция для создания нового узла
node_t *newNode(int data) {
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (new_node == NULL) {
        perror("Не удалось выделить память для нового узла");
        exit(EXIT_FAILURE);
    }
    new_node->data = data; // присваивает полю data нового узла значение, переданное в функцию (data)
    new_node->next = NULL; // Инициализация нового узла 
    new_node->prev = NULL; // Инициализация нового узла 
    return new_node;
}

// Функция для добавления нового узла в конец списка
void append(node_t **head, int data) {
    node_t *new_node = newNode(data);
    if (*head == NULL) { //если список пуст то новый узел становится головой списка
        *head = new_node;
    } else {
        node_t *cur = *head; // сur - текущий узел
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = new_node; //Если список не пуст, функция проходит до последнего узла и добавляет новый узел в конец.
        new_node->prev = cur; // устанавливаем указатель на предыдущий узел 
    }
}

// Функция для печати связного списка 
void printList(node_t *head) {
    node_t *cur = head;
    while (cur != NULL) {
        printf(" %d ->", cur->data);
        cur = cur->next;
    }
    printf(" NULL\n");
}

// Функция для вплетения списка list2 в список list1, чередуя узлы
void binding(node_t **head1, node_t **head2) {
    if (*head2 == NULL) return;

    node_t *cur1 = *head1; // Текущий узел первого списка
    node_t *cur2 = *head2; // Текущий узел второго списка
    node_t *next1, *next2; // Для хранения следующих узлов 

    while (cur1 != NULL && cur2 != NULL) {
        next1 = cur1->next; // Сохраняем следующий узел первого списка
        next2 = cur2->next; // Сохраняем следующий узел второго списка

        cur1->next = cur2;  // Вставляем cur2 после cur1
        cur2->prev = cur1; // Обновляем prev-указатель cur2

        cur2->next = next1;  // Вставить next1 после cur2
        if (next1 != NULL) {
            next1->prev = cur2; // Обновляем prev-указатель next1
        }

        cur1 = next1;// Переходим к следующему узлу первого списка
        cur2 = next2; // Переходим к следующему узлу второго списка
    }

    // Обработка оставшихся элементов в list2 (если есть)
    if (cur2 != NULL) {
        cur1 = *head1;
        if (cur1 == NULL) {
            *head1 = cur2; // Если head1 был NULL, head2 теперь становится головой
        } else {
            while (cur1->next != NULL) {
                cur1 = cur1->next;
            }
            cur1->next = cur2;
            cur2->prev = cur1;
        }
    }
}

int main() {
    node_t *head1 = NULL; // Инициализация головы списка как NULL
    node_t *head2 = NULL;
    node_t *S = NULL;
    node_t *current;  // Текущий узел для навигации
    char move;         // Ввод пользователя для перемещения

    int input;

    // Создание первого связного списка
    printf("Введите числа для первого списка (0 для завершения):\n");
    while (1) {
        scanf("%d", &input);
        if (input == 0) {
            break;
        }
        append(&head1, input); // Добавление введенного числа в список
    }

    // Создание второго связного списка
    printf("Введите числа для второго списка (0 для завершения):\n");
    while (1) {
        scanf("%d", &input);
        if (input == 0) {
            break;
        }
        append(&head2, input);
    }

    S = head2; // Указатель S указывает на начало второго списка

    binding(&head1, &head2);

    // Начало навигации с начала объединенного списка
    current = head1;

    // Цикл навигации
    while (1) {
        if (current == NULL) {
            printf("Список пуст!\n");
            break; // Выход, если список пуст
        }

        printf("Текущее значение: %d\n", current->data);
        printf("Введите команду (W/2 - вверх, S/8 - вниз, D/6 - вправо, A/4 - влево, Q - выход): ");
        scanf(" %c", &move); // Пробел перед %c для игнорирования оставшегося символа новой строки

        move = toupper(move); // Преобразование в верхний регистр для удобства проверки

        switch (move) {
            case 'D':
            case '6':
                if (current->next != NULL) {
                    current = current->next;
                } else {
                    printf("Достигнут конец списка!\n");
                    printf("Вернуться в начало списка (S)? (Y/N): ");
                    char choice;
                    scanf(" %c", &choice);
                    if (toupper(choice) == 'Y') {
                        current = head1;
                    }
                }
                break;
            case 'A':
            case '4':
                if (current->prev != NULL) {
                    current = current->prev;
                } else {
                    printf("Достигнуто начало списка!\n");
                    printf("Вернуться к концу списка (E)? (Y/N): ");
                    char choice;
                    scanf(" %c", &choice);
                    if (toupper(choice) == 'Y') {
                        // Найти конец списка
                        current = head1;
                        while (current->next != NULL) {
                            current = current->next;
                        }
                    }
                }
                break;

            case 'W':
            case '2':
                // Движение вверх: перейти к началу второго списка (S)
                if (S != NULL) {
                    current = S;
                    printf("Переход к началу второго списка.\n");
                } else {
                    printf("Второй список пуст!\n");
                }
                break;

            case 'S':
            case '8':
                // Движение вниз: перейти к началу первого списка (head1)
                if (head1 != NULL) {
                    current = head1;
                    printf("Переход к началу первого списка.\n");
                } else {
                    printf("Первый список пуст!\n");
                }
                break;

            case 'Q':
                printf("Выход из программы.\n");
                goto cleanup;  // Используем goto для удобной очистки памяти перед выходом
            default:
                printf("Неизвестная команда!\n");
        }
    }

    // Освобождение памяти и очистка
    cleanup:
    current = head1;  // Начинаем освобождение с head1
    node_t *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    return 0;
}