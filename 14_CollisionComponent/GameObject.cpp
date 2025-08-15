#include "GameObject.hpp"

GameObject::GameObject() = default;

GameObject::GameObject(SDL_Renderer *renderer, const std::string &sprite_path)
    : m_renderer(renderer)
{
    m_sprite = TextureRectangle(renderer, sprite_path);
}

GameObject::~GameObject() = default;

void GameObject::Update(const double deltaTime, const int x, const int y)
{
    m_sprite.SetPosition(x, y);
    m_collider.SetAbsolutePosition(x, y);
}

void GameObject::Render() const
{
    m_sprite.Render(m_renderer);
    m_collider.Render(m_renderer);
}

TextureRectangle &GameObject::GetTextureRectangle()
{
    return m_sprite;
}

Collider2D &GameObject::GetCollider2D()
{
    return m_collider;
}
