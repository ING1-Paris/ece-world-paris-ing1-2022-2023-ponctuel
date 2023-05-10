cmake_minimum_required(VERSION 3.23)
project(Ponctuel C)

set(CMAKE_C_STANDARD 99)

add_executable(Ponctuel main.c Frogger.c Frogger.h)

target_link_libraries(Ponctuel -lmingw32 -lalleg44)