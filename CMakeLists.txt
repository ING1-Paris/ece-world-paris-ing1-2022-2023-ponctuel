cmake_minimum_required(VERSION 3.23)
project(Allegro C)

set(CMAKE_C_STANDARD 99)

add_executable(Allegro main_guitar_hero.c)

target_link_libraries(Allegro -lmingw32 allegro-4.4.2-monolith-md-debug.dll)
