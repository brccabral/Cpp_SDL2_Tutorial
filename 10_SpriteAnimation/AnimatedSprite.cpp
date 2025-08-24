#include "AnimatedSprite.hpp"

#include "ResourceManager.h"

AnimatedSprite::AnimatedSprite(SDL2pp::Renderer &renderer, const std::string &filepath)
    : texture(renderer, ResourceManager::GetInstance().GetSurface(filepath))
{
}

void AnimatedSprite::Draw(int x, int y, int w, int h)
{
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = w;
    dstRect.h = h;
}

void AnimatedSprite::PlayFrame(int x, int y, int w, int h, int frame)
{
    srcRect.x = x + w * frame;
    srcRect.y = y;
    srcRect.w = w;
    srcRect.h = h;
}

void AnimatedSprite::Render(SDL2pp::Renderer &renderer)
{
    renderer.Copy(texture, srcRect, dstRect);
}
