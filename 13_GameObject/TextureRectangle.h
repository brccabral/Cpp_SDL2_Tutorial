#pragma once
#include <string>
#include <SDL2/SDL.h>


class TextureRectangle
{
public:

    TextureRectangle();
    TextureRectangle(SDL_Renderer *renderer, const std::string &filepath);
    ~TextureRectangle();
    TextureRectangle(const TextureRectangle &);
    TextureRectangle &operator=(const TextureRectangle &);
    TextureRectangle(TextureRectangle &&) noexcept;
    TextureRectangle &operator=(TextureRectangle &&) noexcept;

    void SetDestRect(int x, int y, int w, int h);
    void Render(SDL_Renderer *renderer) const;

    void Draw(int x, int y, int w, int h);

    SDL_bool IsColliding(const TextureRectangle &other) const;

    const SDL_Rect &GetDestRect() const;

private:

    SDL_Texture *texture{};
    SDL_Rect destRect{};
};
