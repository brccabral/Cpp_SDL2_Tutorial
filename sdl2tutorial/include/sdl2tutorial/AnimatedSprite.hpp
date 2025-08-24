#pragma once
#include <string>

#include <SDL2pp/SDL2pp.hh>


class AnimatedSprite
{
public:

    AnimatedSprite(SDL2pp::Renderer &renderer, const std::string &filepath);
    AnimatedSprite(const AnimatedSprite &) = delete;
    AnimatedSprite(const AnimatedSprite &&) = delete;
    AnimatedSprite &operator=(const AnimatedSprite &) = delete;
    AnimatedSprite &operator=(const AnimatedSprite &&) = delete;

    void Draw(int x, int y, int w, int h);
    void PlayFrame(int x, int y, int w, int h, int frame);

    void Render(SDL2pp::Renderer &renderer);

private:

    SDL2pp::Rect srcRect{};
    SDL2pp::Rect dstRect{};
    SDL2pp::Texture texture;
};
