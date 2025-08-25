#include <sdl2tutorial/TextureRectangle.h>
#include <sdl2tutorial/ResourceManager.h>


TextureRectangle::TextureRectangle(SDL2pp::Renderer& renderer, const std::string &filepath)
    : texture(renderer, ResourceManager::GetInstance().GetSurface(filepath))
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

void TextureRectangle::SetDestRect(const int x, const int y, const int w, const int h)
{
    destRect.x = x;
    destRect.y = y;
    destRect.w = w;
    destRect.h = h;
}

void TextureRectangle::Render(SDL2pp::Renderer &renderer)
{
    renderer.Copy(texture, SDL2pp::NullOpt, destRect);
}

void TextureRectangle::Draw(const int x, const int y, const int w, const int h)
{
    destRect.x = x;
    destRect.y = y;
    destRect.w = w;
    destRect.h = h;
}

SDL_bool TextureRectangle::IsColliding(const TextureRectangle &other) const
{
    return (SDL_bool)destRect.Intersects(other.GetDestRect());
}

const SDL2pp::Rect &TextureRectangle::GetDestRect() const
{
    return destRect;
}
