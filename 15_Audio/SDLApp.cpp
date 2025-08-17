#include "SDLApp.hpp"
#include "ResourceManager.h"

SDLApp::SDLApp(const char *title, const int x, const int y, const int w, const int h)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
    }

    window = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
    }
}

SDLApp::~SDLApp()
{
    ResourceManager::Destroy();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDLApp::RunLoop()
{
    static Uint64 now = SDL_GetPerformanceCounter();
    static Uint64 last = 0;
    static double deltaTime = 0.0; // seconds

    while (gameIsRunning)
    {
        last = now;
        now = SDL_GetPerformanceCounter();
        deltaTime = (double) ((now - last) * 1000) / SDL_GetPerformanceFrequency();
        deltaTime /= 1000.0; // convert ms to seconds

        Uint32 buttons = SDL_GetMouseState(&mouseX, &mouseY);

        EventCallback();
        UpdateCallback(deltaTime);

        // clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        RenderCallback();

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

SDL_Renderer *SDLApp::GetRenderer() const
{
    return renderer;
}

int SDLApp::GetMouseX() const
{
    return mouseX;
}

int SDLApp::GetMouseY() const
{
    return mouseY;
}

void SDLApp::StopGame()
{
    gameIsRunning = false;
}

void SDLApp::SetFPS(const int fps)
{
    FPS = fps;
    frameDelay = 1000 / FPS;
}
