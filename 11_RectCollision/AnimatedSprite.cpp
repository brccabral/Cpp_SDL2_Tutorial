#include "AnimatedSprite.hpp"

#include "ResourceManager.h"

AnimatedSprite::AnimatedSprite(SDL_Renderer *renderer, const std::string &filepath)
{
    SDL_Surface *surface = ResourceManager::GetInstance().GetSurface(filepath);
    if (surface != nullptr)
    {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == nullptr)
        {
            fprintf(stderr, "Failed to create AnimatedSprite texture\n");
        }
    }
    else
    {
        fprintf(stderr, "Failed to get surface from %s\n", filepath.c_str());
    }
}

AnimatedSprite::~AnimatedSprite()
{
    SDL_DestroyTexture(texture);
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

void AnimatedSprite::Render(SDL_Renderer *renderer) const
{
    SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
}
