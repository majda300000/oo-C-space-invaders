cmake_minimum_required(VERSION 3.10)
project(ASCII)

find_package(Curses REQUIRED)

add_executable(blinvaders
 main.c src/screen_object.c src/screen_obj_list.c src/hero.c src/game.c src/block.c src/alien.c src/bomb.c
)

target_include_directories(blinvaders PUBLIC ${CURSES_INCLUDE_DIR} inc)
target_link_libraries(blinvaders ${CURSES_LIBRARY})
