#pragma once
#include <string>
#include <SDL2pp/SDL2pp.hh>


class TextureRectangle
{
public:

    TextureRectangle() = default;
    TextureRectangle(SDL2pp::Renderer &renderer, const std::string &filepath);
    TextureRectangle(
            SDL2pp::Renderer &renderer, const std::string &filepath, Uint8 redColorKey,
            Uint8 greenColorKey, Uint8 blueColorKey);
    TextureRectangle(const TextureRectangle &) = delete;
    TextureRectangle &operator=(const TextureRectangle &) = delete;
    TextureRectangle(TextureRectangle &&) noexcept;
    TextureRectangle &operator=(TextureRectangle &&) noexcept;

    void Render(SDL2pp::Renderer &renderer);

    void SetPosition(int x, int y);
    void SetDimensions(int w, int h);
    int GetPositionX() const;
    int GetPositionY() const;

    SDL_bool IsColliding(const TextureRectangle &other) const;

    const SDL2pp::Rect &GetDestRect() const;

private:

    std::unique_ptr<SDL2pp::Texture> texture;
    SDL2pp::Rect destRect{};
};
