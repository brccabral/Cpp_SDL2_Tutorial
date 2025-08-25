#pragma once
#include <functional>
#include <SDL2/SDL.h>

#include "SDL2pp/SDL2pp.hh"


class SDLApp
{
public:

    SDLApp(const char *title, int x, int y, int w, int h);
    virtual ~SDLApp();

    virtual void EventCallback() = 0;
    virtual void RenderCallback() = 0;
    virtual void UpdateCallback(double deltaTime) = 0;

    void RunLoop();

    SDL2pp::Renderer &GetRenderer();
    int GetMouseX() const;
    int GetMouseY() const;
    void StopGame();
    void SetFPS(int fps);

private:

    SDL2pp::SDL sdl;
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;

    int FPS = 60;
    int frameDelay = 1000 / FPS;

    bool gameIsRunning = true;
    int mouseX{}, mouseY{};
};
