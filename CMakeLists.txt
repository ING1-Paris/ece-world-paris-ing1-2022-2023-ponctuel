cmake_minimum_required(VERSION 3.25)
project(Ponctuel C)

set(CMAKE_C_STANDARD 99)

add_executable(Ponctuel main.c Frogger.c Frogger.h guitar_hero.c guitar_hero.h snake.h)

target_link_libraries(Ponctuel -lmingw32 allegro-4.4.2-monolith-md-debug.dll)

file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})