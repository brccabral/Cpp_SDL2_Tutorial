#pragma once
#include <SDL_render.h>
#include <string>


class AnimatedSprite
{
public:

    AnimatedSprite(SDL_Renderer *renderer, const std::string &filepath);
    ~AnimatedSprite();
    AnimatedSprite(const AnimatedSprite &) = delete;
    AnimatedSprite(const AnimatedSprite &&) = delete;
    AnimatedSprite &operator=(const AnimatedSprite &) = delete;
    AnimatedSprite &operator=(const AnimatedSprite &&) = delete;

    void Draw(int x, int y, int w, int h);
    void PlayFrame(int x, int y, int w, int h, int frame);

    void Render(SDL_Renderer *renderer) const;

private:

    SDL_Rect srcRect{};
    SDL_Rect dstRect{};
    SDL_Texture *texture{};
};
