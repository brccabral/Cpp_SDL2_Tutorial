#pragma once

#include <SDL2/SDL.h>
#include "TextureRectangle.h"

class GameObject
{
public:

    GameObject();
    GameObject(SDL_Renderer *renderer, std::string sprite_path);
    ~GameObject();

    void Update();
    void Render();

private:

    TextureRectangle m_sprite{};
    SDL_Renderer *m_renderer{};
};
