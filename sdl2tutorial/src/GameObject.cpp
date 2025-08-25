#include <sdl2tutorial/GameObject.hpp>


GameObject::GameObject(SDL2pp::Renderer *renderer, const std::string &sprite_path)
    : m_sprite(*renderer, sprite_path), m_renderer(renderer)
{
}

GameObject::~GameObject()
{
}

void GameObject::Render()
{
    m_sprite.Render(*m_renderer);
}

TextureRectangle &GameObject::GetTextureRectangle()
{
    return m_sprite;
}
