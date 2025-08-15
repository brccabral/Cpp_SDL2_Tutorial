#pragma once
#include <functional>
#include <SDL2/SDL.h>


class SDLApp
{
public:

    SDLApp(const char *title, int x, int y, int w, int h);
    virtual ~SDLApp();

    virtual void EventCallback() = 0;
    virtual void RenderCallback() = 0;

    void RunLoop();

    SDL_Renderer *GetRenderer() const;
    int GetMouseX() const;
    int GetMouseY() const;
    void StopGame();

private:

    SDL_Window *window{};
    SDL_Renderer *renderer{};

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    bool gameIsRunning = true;
    int mouseX, mouseY;
};
