#pragma once
#include <SDL2pp/SDL2pp.hh>


class SDLApp
{
public:

    SDLApp(Uint32 subsystemFlags, const char *title, int x, int y, int w, int h);
    virtual ~SDLApp();

    virtual void EventCallback() = 0;
    virtual void RenderCallback() = 0;
    virtual void UpdateCallback(double deltaTime) = 0;

    void RunLoop();

    int GetMouseX() const;
    int GetMouseY() const;
    void StopGame();
    void SetFPS(int fps);

protected:

    SDL2pp::Renderer renderer;

private:

    SDL2pp::SDL sdl;
    SDL2pp::Window window;

    int FPS = 60;
    int frameDelay = 1000 / FPS;

    bool gameIsRunning = true;
    int mouseX{}, mouseY{};
};
