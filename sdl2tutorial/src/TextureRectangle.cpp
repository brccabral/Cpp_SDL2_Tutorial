#include <sdl2tutorial/TextureRectangle.h>
#include <sdl2tutorial/ResourceManager.h>


TextureRectangle::TextureRectangle(SDL2pp::Renderer &renderer, const std::string &filepath)
    : texture(new SDL2pp::Texture(renderer, ResourceManager::GetInstance().GetSurface(filepath)))
{
}

TextureRectangle::TextureRectangle(
        SDL2pp::Renderer &renderer, const std::string &filepath, const Uint8 redColorKey,
        const Uint8 greenColorKey,
        const Uint8 blueColorKey)
    : texture(
            new SDL2pp::Texture(
                    renderer,
                    ResourceManager::GetInstance().GetSurface(filepath).SetColorKey(
                            SDL_TRUE, SDL_MapRGB(
                                    ResourceManager::GetInstance().GetSurface(filepath).Get()->
                                    format,
                                    redColorKey, greenColorKey, blueColorKey))))
{
}

TextureRectangle::TextureRectangle(TextureRectangle &&other) noexcept
    : texture(std::move(other.texture)), destRect(other.destRect)
{
}

TextureRectangle &TextureRectangle::operator=(TextureRectangle &&other) noexcept
{
    texture = std::move(other.texture);
    destRect = other.destRect;
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

void TextureRectangle::Render(SDL2pp::Renderer &renderer)
{
    renderer.Copy(*texture, SDL2pp::NullOpt, destRect);
}

SDL_bool TextureRectangle::IsColliding(const TextureRectangle &other) const
{
    return (SDL_bool) destRect.Intersects(other.GetDestRect());
}

const SDL2pp::Rect &TextureRectangle::GetDestRect() const
{
    return destRect;
}
