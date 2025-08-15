#pragma once
#include <string>
#include <SDL2/SDL.h>


class TextureRectangle
{
public:

    TextureRectangle(SDL_Renderer *renderer, const std::string &filepath);
    ~TextureRectangle();
    TextureRectangle(const TextureRectangle &);
    TextureRectangle &operator=(const TextureRectangle &);
    TextureRectangle(TextureRectangle &&) noexcept;
    TextureRectangle &operator=(TextureRectangle &&) noexcept;

    void SetDestRect(int x, int y, int w, int h);
    void Render(SDL_Renderer *renderer) const;

    void Draw(int x, int y, int w, int h);

private:

    SDL_Texture *texture{};
    SDL_Rect destRect{};
};
