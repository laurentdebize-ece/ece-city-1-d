cmake_minimum_required(VERSION 3.23)
project(ece_city_1_d C)

set(CMAKE_C_STANDARD 99)

add_subdirectory(raylib)

add_executable(ece_city_1_d main.c jeu.c jeu.h)
target_link_libraries(ece_city_1_d raylib)