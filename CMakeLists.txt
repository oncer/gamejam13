cmake_minimum_required(VERSION 2.8)
project(crystal)

aux_source_directory(src SRC)

include_directories(src)

add_executable(crystal ${SRC})
target_link_libraries(crystal allegro allegro_image allegro_primitives allegro_font)
