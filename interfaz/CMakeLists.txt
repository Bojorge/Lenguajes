cmake_minimum_required(VERSION 3.13)
project(interfaz C)

set(CMAKE_C_STANDARD 99)

add_executable(interfaz main.c imagenes.c imgs.cpp movimiento.c initFrame.c game.c game.h SelectEnemies.c SelectEnemies.h GameMode.c GameMode.h WaitingRoom.c WaitingRoom.h prueba.c prueba.h)


INCLUDE_DIRECTORIES( allegro/5.0.11/include )

LINK_DIRECTORIES( allegro/5.0.11/lib )


TARGET_LINK_LIBRARIES(interfaz  allegro_acodec
        allegro_audio
        allegro_color
        allegro_dialog
        allegro_image
        allegro_main
        allegro_memfile
        allegro_physfs
        allegro_primitives
        allegro_ttf
        allegro_font
        allegro)
