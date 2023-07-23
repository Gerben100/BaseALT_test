cmake_minimum_required(VERSION 3.17)
project(test_task)

set(CMAKE_CXX_STANDARD 14)

# Создаем разделяемую библиотеку
add_library(test_task SHARED library.cpp library.h)

# Находим и подключаем библиотеку libcurl
find_package(CURL REQUIRED)

# Линкуем библиотеку test_task с libcurl
target_link_libraries(test_task PRIVATE CURL::libcurl)

target_include_directories(test_task PRIVATE "C:/Users/raste/CLionProjects/test_task/include")

# Создаем исполняемый файл
add_executable(test_task_main main.cpp)

# Линкуем исполняемый файл с библиотекой test_task
target_link_libraries(test_task_main PRIVATE test_task)

target_include_directories(test_task_main PRIVATE "C:/Users/raste/CLionProjects/test_task/include")