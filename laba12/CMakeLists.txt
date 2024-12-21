# Задание: Создать библиотеку из background.c и слинковать ее с библиотекой pipes
set(SOURCES background.c)
add_library(background ${SOURCES})
include_directories("../pipes")
target_link_libraries(background pipes)
