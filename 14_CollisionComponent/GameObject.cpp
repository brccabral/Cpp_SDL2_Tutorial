#include "GameObject.hpp"

GameObject::GameObject() = default;

GameObject::GameObject(SDL_Renderer *renderer, const std::string &sprite_path)
    : m_renderer(renderer)
{
    m_sprite = TextureRectangle(renderer, sprite_path);
}

GameObject::~GameObject() = default;

void GameObject::Update(const double deltaTime)
{
    m_collider.SetAbsolutePosition(m_sprite.GetDestRect().x, m_sprite.GetDestRect().y);
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
