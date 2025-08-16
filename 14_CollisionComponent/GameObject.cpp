#include "GameObject.hpp"

GameObject::GameObject() = default;

GameObject::GameObject(SDL_Renderer *renderer)
    : m_renderer(renderer)
{
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

void GameObject::SetTextureRect(const std::string &sprite_path)
{
    m_sprite = TextureRectangle(m_renderer, sprite_path);
}

void GameObject::SetTextureRect(
        const std::string &sprite_path, Uint8 redColorKey, Uint8 greenColorKey, Uint8 blueColorKey)
{
    m_sprite = TextureRectangle(m_renderer, sprite_path, redColorKey, greenColorKey, blueColorKey);
}

TextureRectangle &GameObject::GetTextureRectangle()
{
    return m_sprite;
}

Collider2D &GameObject::GetCollider2D()
{
    return m_collider;
}
