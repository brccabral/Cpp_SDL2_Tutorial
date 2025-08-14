#pragma once
#include <string>
#include <SDL2/SDL.h>


class TextureRectangle
{
public:

    TextureRectangle(SDL_Renderer *renderer, const std::string &filepath);
    ~TextureRectangle();

    void SetDestRect(int x, int y, int w, int h);
    void Render(SDL_Renderer *renderer) const;

private:

    SDL_Texture *texture{};
    SDL_Rect destRect{};
};
