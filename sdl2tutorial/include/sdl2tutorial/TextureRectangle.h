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

    void SetDestRect(int x, int y, int w, int h);
    void Render(SDL2pp::Renderer *renderer);

private:

    SDL2pp::Texture texture;
    SDL2pp::Rect destRect{};
};
