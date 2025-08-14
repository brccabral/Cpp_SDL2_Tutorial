#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "TextureRectangle.h"


int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
            "C++ SDL2 Window",
            20,
            20,
            640,
            480,
            SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    constexpr int FPS = 60;
    constexpr int frameDelay = 1000 / FPS;

    {
        bool gameIsRunning = true;

        Uint64 now = SDL_GetPerformanceCounter();
        Uint64 last = 0;
        double deltaTime = 0.0; // seconds

        std::vector<TextureRectangle> textureRects;
        for (auto i = 0; i < 20; ++i)
        {
            auto &tr = textureRects.emplace_back(renderer, "images/test.bmp");
            tr.SetDestRect((50 * i) % 600, (50 * i) % 400, 150, 150);
        }

        while (gameIsRunning)
        {
            last = now;
            now = SDL_GetPerformanceCounter();
            deltaTime = (double) ((now - last) * 1000) / SDL_GetPerformanceFrequency();
            deltaTime /= 1000.0; // convert ms to seconds

            SDL_Event event;
            int mouseX, mouseY;
            Uint32 buttons = SDL_GetMouseState(&mouseX, &mouseY);

            // Start our event loop
            while (SDL_PollEvent(&event))
            {
                // Handle each specific event
                if (event.type == SDL_QUIT)
                {
                    gameIsRunning = false;
                }
                if (event.type == SDL_KEYDOWN)
                {
                    if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                    {
                        gameIsRunning = false;
                    }
                }
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                }
            }

            // clear screen
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(renderer);

            // draw stuff
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawLine(renderer, 10, 10, mouseX, mouseY);

            for (const auto &texture_rect: textureRects)
            {
                texture_rect.Render(renderer);
            }

            // show renderer
            SDL_RenderPresent(renderer);

            // FPS
            const Uint64 frameTime = ((SDL_GetPerformanceCounter() - now) * 1000) /
                                     SDL_GetPerformanceFrequency();
            if (frameDelay > frameTime)
            {
                SDL_Delay((Uint32) (frameDelay - frameTime));
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
