cmake_minimum_required(VERSION 3.17)
project(test_task)

set(CMAKE_CXX_STANDARD 14)

# Создаем разделяемую библиотеку
add_library(test_task SHARED library.cpp library.h)

# Находим и подключаем библиотеки libcurl и nlohmann/json
find_package(CURL REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)
include_directories(${CURL_INCLUDE_DIRS} ${nlohmann_json_INCLUDE_DIRS})

# Создаем исполняемый файл
add_executable(test_task_main2 main.cpp)

# Линкуем исполняемый файл с библиотекой test_task и библиотеками libcurl и nlohmann/json
target_link_libraries(test_task_main2 PRIVATE test_task ${CURL_LIBRARIES} nlohmann_json::nlohmann_json pthread)

