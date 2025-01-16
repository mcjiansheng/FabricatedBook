// SDL word image
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#undef main

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    TTF_Init();

    SDL_Window *window = SDL_CreateWindow("Hello,World!", 100, 100, 1000, 750, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface *surface_background = IMG_Load("./img/image.jpg");
    SDL_Texture *texture_background = SDL_CreateTextureFromSurface(renderer, surface_background);

    SDL_Rect rect_background = {.x = 0, .y = 0};
    SDL_QueryTexture(texture_background, NULL, NULL, &rect_background.w, &rect_background.h);

    TTF_Font *font_title = TTF_OpenFont("./res/ys_zt.ttf", 16);
//    if (font_title != NULL) {
//        printf("font isn't null\n");
//    }
    SDL_Color Color_title = {0xff, 0xff, 0xff, 0xff};
    // 使用 UTF-8 编码的字符串
    SDL_Surface *surface_title = TTF_RenderUTF8_Blended(font_title, "game start", Color_title);
    SDL_Texture *texture_title = SDL_CreateTextureFromSurface(renderer, surface_title);

    SDL_Rect rect_title = {.x = 300, .y = 200};
    SDL_QueryTexture(texture_title, NULL, NULL, &rect_title.w, &rect_title.h);

    SDL_RenderCopy(renderer, texture_background, NULL, &rect_background);
    SDL_RenderCopy(renderer, texture_title, NULL, &rect_title);
    SDL_RenderPresent(renderer);

    SDL_Delay(3000);

    // 正确释放资源，避免重复释放
    SDL_FreeSurface(surface_background);
    SDL_DestroyTexture(texture_background);
    SDL_DestroyTexture(texture_title);
    TTF_CloseFont(font_title);

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
    return 0;
}