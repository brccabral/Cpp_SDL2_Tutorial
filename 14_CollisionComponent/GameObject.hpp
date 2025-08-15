#pragma once

#include <SDL2/SDL.h>

#include "Collider2D.hpp"
#include "TextureRectangle.h"

class GameObject
{
public:

    GameObject();
    GameObject(SDL_Renderer *renderer, const std::string &sprite_path);
    ~GameObject();

    void Update(double deltaTime, int x, int y);
    void Render() const;

    TextureRectangle &GetTextureRectangle();
    Collider2D &GetCollider2D();

private:

    TextureRectangle m_sprite{};
    SDL_Renderer *m_renderer{};
    Collider2D m_collider{};
};
