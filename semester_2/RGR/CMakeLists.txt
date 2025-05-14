cmake_minimum_required(VERSION 3.10)
project(MatrixInversion C)

set(CMAKE_C_STANDARD 99)

add_executable(matrix_app
    main.c
    matrix.c
)

# Тесты
find_package(cmocka REQUIRED)
add_executable(matrix_tests
    test_matrix.c
    matrix.c
)
target_link_libraries(matrix_tests cmocka)
