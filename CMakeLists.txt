cmake_minimum_required(VERSION 3.29)
project(projekt_main C)

set(CMAKE_C_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_subdirectory(src)
enable_testing()
add_executable(create_map
        src/map_creation/create_map.c
        src/map_creation/create_file.c)
