cmake_minimum_required(VERSION 3.17)
project(test)

set(CMAKE_CXX_STANDARD 14)

add_library(test SHARED library.cpp library.h)

find_package(CURL REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(Catch2 REQUIRED)

include_directories(${Catch2_INCLUDE_DIRS} ${CURL_INCLUDE_DIRS} ${nlohmann_json_INCLUDE_DIRS})

add_executable(test_test test.cpp)

target_link_libraries(test_test PRIVATE test ${Catch2_INCLUDE_DIRS} ${CURL_LIBRARIES} ${nlohmann_json_INCLUDE_DIRS} pthread)
