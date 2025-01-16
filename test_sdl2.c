//SDL word image

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#undef main

void quitgame() {
    Mix_Quit();
    SDL_Quit();
    exit(0);
}

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    Mix_Init(MIX_INIT_MP3);

    SDL_Window *window = SDL_CreateWindow("Hello,World!", 100, 100, 1000, 750, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048);

    Mix_Chunk *sound = Mix_LoadWAV("");

    SDL_Event event;
    while (1) {
        while (SDL_WaitEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    puts("Exited.");
                    quitgame();
                    return 0;
                case SDL_MOUSEBUTTONDOWN:
                    printf("Button down at (%d,%d)\n", event.button.x, event.button.y);
                    break;
                case SDL_MOUSEBUTTONUP:
                    printf("Button up at (%d,%d)\n", event.button.x, event.button.y);
                    break;
                case SDL_KEYDOWN:
                    printf("Key down: %s\n", SDL_GetKeyName(event.key.keysym.sym));
                    break;
                case SDL_KEYUP:
                    printf("Key up: %s\n", SDL_GetKeyName(event.key.keysym.sym));
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        puts("Exited by key.");
                        quitgame();
                        return 0;
                    }
                    break;
                default:
                    break;
            }
            fflush(stdout);
        }
        SDL_Delay(5);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    Mix_CloseAudio();

    Mix_Quit();
    SDL_Quit();
    return 0;
}
