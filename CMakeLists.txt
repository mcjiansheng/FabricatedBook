cmake_minimum_required(VERSION 3.29)
project(SlaytheSpire C)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_C_STANDARD 17)

include_directories("./SDL2-2.26.0-allinone/x86_64-w64-mingw32/include")
link_directories("./SDL2-2.26.0-allinone/x86_64-w64-mingw32/lib")


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

add_executable(FabricBook game.c
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
        tools/fight.c
        tools/fight.h
        tools/collection.c
        tools/collection.h
        tools/events.c
        tools/events.h
        tools/shop.c
        tools/shop.h
)
target_link_libraries(FabricBook PUBLIC ${SDL_LIBRARIES})
