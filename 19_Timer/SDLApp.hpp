#pragma once
#include <SDL2/SDL.h>


class SDLApp
{
public:

    SDLApp(Uint32 subsystemFlags, const char *title, int x, int y, int w, int h);
    virtual ~SDLApp();

    virtual void EventCallback() = 0;
    virtual void RenderCallback() = 0;
    virtual void UpdateCallback(double deltaTime) = 0;

    void RunLoop();

    [[nodiscard]] SDL_Renderer *GetRenderer() const;
    [[nodiscard]] int GetMouseX() const;
    [[nodiscard]] int GetMouseY() const;
    void StopGame();
    void SetFPS(int fps);

    int GetWindowWidth() const;
    int GetWindowHeight() const;

    void StopMixer() const;
    void PauseMixer() const;

    // 0 to 128
    void SetVolume(int volume) const;
    int GetVolume() const;

protected:

    SDL_Renderer *renderer{};
    bool isMixInitiated;

private:

    SDL_Window *window{};

    int FPS = 60;
    int frameDelay = 1000 / FPS;

    bool gameIsRunning = true;
    int mouseX{}, mouseY{};
};
