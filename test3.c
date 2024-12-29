#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
// 窗口尺寸
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// 角色位置和尺寸
#define CHARACTER_WIDTH 200
#define CHARACTER_HEIGHT 300
#define CHARACTER1_X 200
#define CHARACTER1_Y 150
#define CHARACTER2_X 400
#define CHARACTER2_Y 150

// 函数声明
SDL_Texture *LoadTexture(const char *file, SDL_Renderer *renderer, SDL_Color key);

int main(int argc, char *argv[]) {
    // 初始化 SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // 创建窗口
    SDL_Window *window = SDL_CreateWindow("角色选择", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                          SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // 创建渲染器
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 加载角色立绘
    SDL_Color white = {255, 255, 255}; // 白色背景
    SDL_Texture *character1 = LoadTexture("./img/Character_Selection_Warrior.png", renderer, white);
    SDL_Texture *character2 = LoadTexture("./img/Character_Selection_Mage.png", renderer, white);

    if (!character1 || !character2) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 游戏循环
    bool running = true;
    int selectedCharacter = 0; // 0 表示未选择，1 表示角色1，2 表示角色2
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX = e.button.x;
                int mouseY = e.button.y;

                // 检测是否点击角色1
                if (mouseX >= CHARACTER1_X && mouseX <= CHARACTER1_X + CHARACTER_WIDTH &&
                    mouseY >= CHARACTER1_Y && mouseY <= CHARACTER1_Y + CHARACTER_HEIGHT) {
                    selectedCharacter = 1;
                    running = false;
                }
                    // 检测是否点击角色2
                else if (mouseX >= CHARACTER2_X && mouseX <= CHARACTER2_X + CHARACTER_WIDTH &&
                         mouseY >= CHARACTER2_Y && mouseY <= CHARACTER2_Y + CHARACTER_HEIGHT) {
                    selectedCharacter = 2;
                    running = false;
                }
            }
        }

        // 清空屏幕
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // 黑色背景
        SDL_RenderClear(renderer);

        // 渲染角色1
        SDL_Rect char1Rect = {CHARACTER1_X, CHARACTER1_Y, CHARACTER_WIDTH, CHARACTER_HEIGHT};
        SDL_RenderCopy(renderer, character1, NULL, &char1Rect);

        // 渲染角色2
        SDL_Rect char2Rect = {CHARACTER2_X, CHARACTER2_Y, CHARACTER_WIDTH, CHARACTER_HEIGHT};
        SDL_RenderCopy(renderer, character2, NULL, &char2Rect);

        // 更新屏幕
        SDL_RenderPresent(renderer);
    }

    // 输出选择结果
    if (selectedCharacter == 1) {
        printf("选择了角色1\n");
    } else if (selectedCharacter == 2) {
        printf("选择了角色2\n");
    }

    // 清理资源
    SDL_DestroyTexture(character1);
    SDL_DestroyTexture(character2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

// 加载图像并设置透明色
SDL_Texture *LoadTexture(const char *file, SDL_Renderer *renderer, SDL_Color key) {
    SDL_Surface *tempSurface = IMG_Load(file);
    if (!tempSurface) {
        printf("IMG_Load Error: %s\n", IMG_GetError());
        return NULL;
    }

    // 设置透明色
    SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, key.r, key.g, key.b));

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    if (!texture) {
        printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
    }
    return texture;
}
