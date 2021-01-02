cmake_minimum_required(VERSION 3.11)
project(finalproject)

set(CMAKE_C_STANDARD 11)

file(GLOB SOURCES CONFIGURE_DEPENDS *.h, *.c)

#include project and allegro headers
include_directories(include)
include_directories(allegro/include)
link_directories(allegro/lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR})
set(SOURCES
        src/main.c
        src/game.c
        src/scene_menu.c
        src/scene_settings.c
        src/scene_start.c
        src/shared.c
        src/utility.c
        )
add_executable(finalproject ${SOURCES})


target_link_libraries(
        finalproject
        allegro_acodec
        allegro_audio
        allegro_color
        allegro_dialog
        allegro_font
        allegro_image
        allegro_main
        allegro_memfile
#        allegro_physfs
        allegro_primitives
        allegro
        allegro_ttf
#        allegro_video
        -lm
)
