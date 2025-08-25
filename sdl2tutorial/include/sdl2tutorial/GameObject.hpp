#pragma once

#include <SDL2/SDL.h>
#include "TextureRectangle.h"

class GameObject
{
public:

    GameObject();
    GameObject(SDL2pp::Renderer *renderer, const std::string &sprite_path);
    ~GameObject();

    void Update();
    void Render();

    TextureRectangle &GetTextureRectangle();

private:

    TextureRectangle m_sprite;
    SDL2pp::Renderer *m_renderer{};
};
