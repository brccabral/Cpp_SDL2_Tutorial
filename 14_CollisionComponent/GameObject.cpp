#include "GameObject.hpp"

GameObject::GameObject() = default;

GameObject::GameObject(SDL_Renderer *renderer, std::string sprite_path)
    : m_renderer(renderer)
{
    m_sprite = TextureRectangle(renderer, sprite_path);
}

GameObject::~GameObject() = default;

void GameObject::Render() const
{
    m_sprite.Render(m_renderer);
}

TextureRectangle &GameObject::GetTextureRectangle()
{
    return m_sprite;
}

Collider2D &GameObject::GetCollider2D()
{
    return m_collider;
}
