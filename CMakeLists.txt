cmake_minimum_required(VERSION 3.29)
project(SlaytheSpire C)

set(CMAKE_C_STANDARD 17)

include_directories("D:/mingw(CLion+VSC)/SDL2-2.26.0-allinone/x86_64-w64-mingw32/include")
link_directories("D:/mingw(CLion+VSC)/SDL2-2.26.0-allinone/x86_64-w64-mingw32/lib")


set(SDL_LIBRARIES
        mingw32
        SDL2main
        SDL2
        SDL2_image
        SDL2_mixer
        SDL2_ttf
)
add_executable(botton tools/button.c)
target_link_libraries(botton PUBLIC ${SDL_LIBRARIES})

add_executable(SlaytheSpire game.c
        tools/button.h
        tools/button.c
        tools/Saves.c
        tools/Saves.h
        tools/Color.c
        tools/Color.h
        tools/gamecreater.c
        tools/gamecreater.h
        tools/card.c
        tools/card.h
        tools/videos.c
        tools/videos.h
        tools/map.c
        tools/map.h
        tools/nodes_event.c
        tools/nodes_event.h
)
target_link_libraries(SlaytheSpire PUBLIC ${SDL_LIBRARIES})

add_executable(test test_sdl.c)
target_link_libraries(test PUBLIC ${SDL_LIBRARIES})

add_executable(test2 test_sdl2.c)
target_link_libraries(test2 PUBLIC ${SDL_LIBRARIES})
add_executable(test3 test3.c)
target_link_libraries(test3 PUBLIC ${SDL_LIBRARIES})

add_executable(testmap tools/map.c
        tools/button.h
        tools/button.c
        tools/Saves.c
        tools/Saves.h
        tools/Color.c
        tools/Color.h
        tools/gamecreater.c
        tools/gamecreater.h
        tools/card.c
        tools/card.h
        tools/videos.c
        tools/videos.h
        tools/map.h)
target_link_libraries(testmap PUBLIC ${SDL_LIBRARIES})