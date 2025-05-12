#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "matrix_test8.h"
#include <stdio.h>

// Тест функции matrix
static void test_matrix_output(void **state) {
    (void)state; // Неиспользуемый параметр
    
    // Перенаправляем stdout в буфер
    freopen("test_output.txt", "w+", stdout);
    
    int arr[2][2] = {{1, 2}, {3, 4}};
    matrix(2, 2, arr);
    
    // Возвращаем stdout
    freopen("/dev/tty", "a", stdout);
    
    // Проверяем содержимое файла
    FILE *f = fopen("test_output.txt", "r");
    char buffer[100];
    fgets(buffer, 100, f);
    assert_string_equal(buffer, " 1 2\n");
    fgets(buffer, 100, f);
    assert_string_equal(buffer, " 3 4\n");
    fclose(f);
}

// Тест определителя для матрицы 1x1
static void test_determinant_1x1(void **state) {
    (void)state;
    int arr[1][1] = {{5}};
    assert_int_equal(determinant(1, arr), 5);
}

// Тест определителя для матрицы 2x2
static void test_determinant_2x2(void **state) {
    (void)state;
    int arr[2][2] = {{1, 2}, {3, 4}};
    assert_int_equal(determinant(2, arr), -2);
}

// Тест определителя для матрицы 3x3
static void test_determinant_3x3(void **state) {
    (void)state;
    int arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    assert_int_equal(determinant(3, arr), 0);
}

// Тест метода Крамера для системы 2x2
static void test_Kramer_2x2(void **state) {
    (void)state;
    
    // Перенаправляем stdout в буфер
    freopen("test_kramer_output.txt", "w+", stdout);
    
    int arr[2][2] = {{2, 1}, {1, 3}};
    int B[2] = {4, 5};
    Kramer(2, arr, B);
    
    // Возвращаем stdout
    freopen("/dev/tty", "a", stdout);
    
    // Проверяем содержимое файла
    FILE *f = fopen("test_kramer_output.txt", "r");
    char buffer[100];
    fgets(buffer, 100, f);
    assert_string_equal(buffer, "Решение системы:\n");
    fgets(buffer, 100, f);
    assert_string_equal(buffer, "x1 = 1.40, x2 = 1.20\n");
    fclose(f);
}

// Тест метода Крамера для вырожденной системы
static void test_Kramer_singular(void **state) {
    (void)state;
    
    freopen("test_kramer_singular.txt", "w+", stdout);
    
    int arr[2][2] = {{1, 2}, {2, 4}}; // Вырожденная матрица
    int B[2] = {3, 6};
    Kramer(2, arr, B);
    
    freopen("/dev/tty", "a", stdout);
    
    FILE *f = fopen("test_kramer_singular.txt", "r");
    char buffer[100];
    fgets(buffer, 100, f);
    assert_string_equal(buffer, "Система не имеет единственного решения\n");
    fclose(f);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_matrix_output),
        cmocka_unit_test(test_determinant_1x1),
        cmocka_unit_test(test_determinant_2x2),
        cmocka_unit_test(test_determinant_3x3),
        cmocka_unit_test(test_Kramer_2x2),
        cmocka_unit_test(test_Kramer_singular),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}