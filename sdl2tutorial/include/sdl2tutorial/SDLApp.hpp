#pragma once
#include <set>
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

    int GetWindowWidth() const;
    int GetWindowHeight() const;

    // if `callback` is recurring (returns value > 0), then the same `param` is used
    // in the next call. Therefore, `param` must outlive the Timer.
    // `callback` must be free function or static
    SDL_TimerID AddTimer(Uint32 delay, SDL_TimerCallback callback, void *param);
    void RemoveTimer(SDL_TimerID id);

private:

    SDL2pp::SDL sdl;
    SDL2pp::Window window; // must be declared after sdl

    int FPS = 60;
    int frameDelay = 1000 / FPS;

    bool gameIsRunning = true;
    int mouseX{}, mouseY{};

    std::set<SDL_TimerID> m_timers;

protected:

    SDL2pp::Renderer renderer; // must be declared after window
    SDL2pp::SDLTTF ttf;
};
