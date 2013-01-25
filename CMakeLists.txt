cmake_minimum_required(VERSION 2.8)
project(gamejam13)

aux_source_directory(src SRC)

include_directories(src)

add_executable(gamejam13 ${SRC})
target_link_libraries(gamejam13 allegro allegro_image allegro_primitives allegro_font allegro_acodec allegro_audio)
