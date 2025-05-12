cmake_minimum_required(VERSION 3.10)
project(tests)

# Настройка стандарта C
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Находим библиотеку CMocka для тестов
find_package(cmocka REQUIRED)

# Создаем библиотеку из основного кода
add_library(matrix_lib proga8_func.c)

# Создаем основное приложение (без тестов)
add_executable(proga8_func proga8_main.c)  # новый файл для main()
target_link_libraries(proga8_func matrix_lib)

# Создаем тестовый исполняемый файл
add_executable(test8 test8.c)
target_link_libraries(test8 matrix_lib cmocka)

# Подключаем заголовки
target_include_directories(matrix_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(test8 PRIVATE ${CMOCKA_INCLUDE_DIRS})

# Настройка тестирования
enable_testing()
add_test(NAME test8 COMMAND test8)
add_custom_target(run_tests COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)