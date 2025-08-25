#pragma once
#include <string>
#include <SDL2pp/SDL2pp.hh>


class TextureRectangle
{
public:

    TextureRectangle(SDL2pp::Renderer& renderer, const std::string &filepath);
    TextureRectangle(const TextureRectangle &) = delete;
    TextureRectangle &operator=(const TextureRectangle &) = delete;
    TextureRectangle(TextureRectangle &&) noexcept;
    TextureRectangle &operator=(TextureRectangle &&) noexcept;

    void Render(SDL2pp::Renderer &renderer);

    void SetPosition(int x, int y);
    void SetDimensions(int w, int h);

    SDL_bool IsColliding(const TextureRectangle &other) const;

    const SDL2pp::Rect &GetDestRect() const;

private:

    SDL2pp::Texture texture;
    SDL2pp::Rect destRect{};
};
