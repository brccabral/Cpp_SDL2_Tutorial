#include "GameObject.hpp"

GameObject::GameObject()
{
}

GameObject::GameObject(SDL_Renderer *renderer, std::string sprite_path)
    : m_renderer(renderer)
{
    m_sprite = TextureRectangle(renderer, sprite_path);
}

GameObject::~GameObject()
{
}

void GameObject::Render()
{
    m_sprite.Render(m_renderer);
}
