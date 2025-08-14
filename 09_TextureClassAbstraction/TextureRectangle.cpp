#include "TextureRectangle.h"

TextureRectangle::TextureRectangle(SDL_Renderer *renderer, const std::string &filepath)
{
    SDL_Surface *surface = SDL_LoadBMP(filepath.c_str());
    if (surface == nullptr)
    {
        fprintf(stderr, "SDL_LoadBMP Error: %s\n", SDL_GetError());
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr)
    {
        fprintf(stderr, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
    }
    SDL_FreeSurface(surface);
}

TextureRectangle::~TextureRectangle()
{
    SDL_DestroyTexture(texture);
}

TextureRectangle::TextureRectangle(const TextureRectangle &other)
    : texture(other.texture), destRect(other.destRect)
{
}

TextureRectangle &TextureRectangle::operator=(const TextureRectangle &other)
{
    texture = other.texture;
    destRect = other.destRect;
    return *this;
}

TextureRectangle::TextureRectangle(TextureRectangle &&other) noexcept
    : texture(other.texture), destRect(other.destRect)
{
    other.texture = nullptr;
}

TextureRectangle &TextureRectangle::operator=(TextureRectangle &&other) noexcept
{
    texture = other.texture;
    destRect = other.destRect;
    other.texture = nullptr;
    return *this;
}

void TextureRectangle::SetDestRect(const int x, const int y, const int w, const int h)
{
    destRect.x = x;
    destRect.y = y;
    destRect.w = w;
    destRect.h = h;
}

void TextureRectangle::Render(SDL_Renderer *renderer) const
{
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}
