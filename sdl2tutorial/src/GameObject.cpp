#include <sdl2tutorial/GameObject.hpp>


GameObject::GameObject(SDL2pp::Renderer *renderer)
    : m_renderer(renderer)
{
}

GameObject::~GameObject() = default;

void GameObject::Update(const double deltaTime)
{
    for (auto &m_collider: m_colliders)
    {
        m_collider.Update(deltaTime);
    }
}
void GameObject::Render()
{
    m_sprite.Render(*m_renderer);
}

void GameObject::SetTextureRect(const std::string &sprite_path)
{
    m_sprite = TextureRectangle(*m_renderer, sprite_path);
}

void GameObject::SetTextureRect(
        const std::string &sprite_path, Uint8 redColorKey, Uint8 greenColorKey, Uint8 blueColorKey)
{
    m_sprite = TextureRectangle(*m_renderer, sprite_path, redColorKey, greenColorKey, blueColorKey);
}

void GameObject::SetPosition(const int x, const int y)
{
    m_sprite.SetPosition(x, y);
    for (auto &m_collider: m_colliders)
    {
        m_collider.SetParentPosition(x, y);
    }
}

TextureRectangle &GameObject::GetTextureRectangle()
{
    return m_sprite;
}

Collider2D &GameObject::GetCollider2D(const int index)
{
    return m_colliders.at(index);
}

const std::vector<Collider2D> &GameObject::GetAllColliders() const
{
    return m_colliders;
}

int GameObject::AddCollider2D()
{
    m_colliders.emplace_back();
    return m_colliders.size() - 1;
}

SDL_bool GameObject::IsColliding(const std::vector<Collider2D> &other_colliders) const
{
    for (auto &m_collider: m_colliders)
    {
        for (auto &other_collider: other_colliders)
        {
            if (m_collider.IsColliding(other_collider))
            {
                return SDL_TRUE;
            }
        }
    }
    return SDL_FALSE;
}
