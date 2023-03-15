#include "core.h"

#include <stdio.h>

#define SCREEN_WIDTH 384
#define SCREEN_HEIGHT 216

// current game state
typedef struct game_state 
{
    SDL_Window *window;
    SDL_Texture *texture;
    SDL_Renderer *renderer;
    u32 pixels[SCREEN_WIDTH * SCREEN_HEIGHT];

    bool quit;

} game_state;

int main(int argc, char *argv[]) 
{
    game_state state;

    random_seed(13);

    // sdl boilerplate
    ASSERT(!SDL_Init(SDL_INIT_VIDEO), "SDL failed to initialize: %s\n", SDL_GetError());

    state.window = 
        SDL_CreateWindow(
            "wolf",
            SDL_WINDOWPOS_CENTERED_DISPLAY(0),
            SDL_WINDOWPOS_CENTERED_DISPLAY(0),
            1280,
            720,
            SDL_WINDOW_ALLOW_HIGHDPI);

    ASSERT(state.window, "failed to create SDL window: %s\n", SDL_GetError());

    state.renderer = SDL_CreateRenderer(state.window, -1, SDL_RENDERER_PRESENTVSYNC);

    ASSERT(state.renderer, "failed to create SDL renderer: %s\n", SDL_GetError());

    state.texture =
        SDL_CreateTexture(
            state.renderer,
            SDL_PIXELFORMAT_ABGR8888,
            SDL_TEXTUREACCESS_STREAMING,
            SCREEN_WIDTH,
            SCREEN_HEIGHT);

    ASSERT(state.texture, "failed to create SDL texture: %s\n", SDL_GetError());

    // gameloop
    state.quit = false;
    while (state.quit != true) 
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) 
        {
            switch (event.type) 
            {
                case SDL_QUIT: 
                {
                    state.quit = true;
                    break;
                }
            }
        }

        // clear screen
        memset(state.pixels, 0, sizeof(state.pixels));        

        // set every pixel to a random color
        for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
        {
            state.pixels[i] = random_get();
        }

        // display state.texture 
        SDL_UpdateTexture(state.texture, NULL, state.pixels, SCREEN_WIDTH * 4);
        SDL_RenderCopyEx(
            state.renderer,
            state.texture,
            NULL,
            NULL,
            0.0,
            NULL,
            SDL_FLIP_VERTICAL);
        SDL_RenderPresent(state.renderer);
    }

    return 0;
}