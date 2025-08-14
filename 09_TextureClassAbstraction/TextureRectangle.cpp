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
