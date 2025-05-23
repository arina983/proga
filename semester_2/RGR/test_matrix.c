#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "matrix.h"
#include <math.h>

// Тест с корректными входными данными (матрица должна иметь обратную)
static void test_inverse_matrix_correct(void **state) {
    (void)state; 
    
    int n = 2;
    int error = 0;
    
    double **matrix = memory_matrix(n, n);
    matrix[0][0] = 4; matrix[0][1] = 7;
    matrix[1][0] = 2; matrix[1][1] = 6;
    
    double **inverse = inverse_matrix(n, matrix, &error);

    assert_int_equal(error, 0);

    double expected[2][2] = {
        {0.6, -0.7},
        {-0.2, 0.4}
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            assert_true(fabs(inverse[i][j] - expected[i][j]) < EPSILON);
        }
    }

    free_matrix(n, matrix);
    free_matrix(n, inverse);
}

static void test_inverse_matrix_incorrect(void **state) {
    (void)state; 
    
    int n = 2;
    int error = 0;
    
    // (определитель = 0)
    double **matrix = memory_matrix(n, n);
    matrix[0][0] = 1; matrix[0][1] = 2;
    matrix[1][0] = 2; matrix[1][1] = 4;
    
    double **inverse = inverse_matrix(n, matrix, &error);

    assert_int_equal(error, 1);
    assert_null(inverse);

    free_matrix(n, matrix);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_inverse_matrix_correct),
        cmocka_unit_test(test_inverse_matrix_incorrect),
    };
    
    return cmocka_run_group_tests(tests, NULL, NULL);
}
