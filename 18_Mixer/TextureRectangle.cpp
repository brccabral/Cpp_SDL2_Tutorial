#include "TextureRectangle.h"
#include "ResourceManager.h"


TextureRectangle::TextureRectangle() = default;

TextureRectangle::TextureRectangle(SDL_Renderer *renderer, const std::string &filepath)
{
    auto *surface = ResourceManager::GetInstance().GetSurface(filepath);
    if (surface != nullptr)
    {
        SDL_SetColorKey(surface, SDL_FALSE, SDL_MapRGB(surface->format, 0, 0, 0));
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == nullptr)
        {
            fprintf(stderr, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        }
    }
    else
    {
        fprintf(stderr, "TextureRectangle Error: %s\n", SDL_GetError());
    }
}

TextureRectangle::TextureRectangle(
        SDL_Renderer *renderer, const std::string &filepath, const Uint8 redColorKey,
        const Uint8 greenColorKey,
        const Uint8 blueColorKey)
{
    auto *surface = ResourceManager::GetInstance().GetSurface(filepath);
    if (surface != nullptr)
    {
        SDL_SetColorKey(
                surface, SDL_TRUE, SDL_MapRGB(
                        surface->format, redColorKey, greenColorKey, blueColorKey));
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == nullptr)
        {
            fprintf(stderr, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        }
    }
    else
    {
        fprintf(stderr, "TextureRectangle Error: %s\n", SDL_GetError());
    }
}

TextureRectangle::~TextureRectangle()
{
    SDL_DestroyTexture(texture);
}

TextureRectangle::TextureRectangle(const TextureRectangle &other) = default;

TextureRectangle &TextureRectangle::operator=(const TextureRectangle &other) = default;

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

void TextureRectangle::SetPosition(const int x, const int y)
{
    destRect.x = x;
    destRect.y = y;
}

void TextureRectangle::SetDimensions(const int w, const int h)
{
    destRect.w = w;
    destRect.h = h;
}

int TextureRectangle::GetPositionX() const
{
    return destRect.x;
}

int TextureRectangle::GetPositionY() const
{
    return destRect.y;
}

void TextureRectangle::Render(SDL_Renderer *renderer) const
{
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}

SDL_bool TextureRectangle::IsColliding(const TextureRectangle &other) const
{
    return SDL_HasIntersection(&destRect, &other.GetDestRect());
}

const SDL_Rect &TextureRectangle::GetDestRect() const
{
    return destRect;
}
