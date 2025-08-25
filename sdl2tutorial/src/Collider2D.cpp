#include <sdl2tutorial/Collider2D.hpp>

SDL_bool Collider2D::IsColliding(const Collider2D &other) const
{
    return SDL_HasIntersection(&colliderRect, &other.colliderRect);
}

void Collider2D::SetRelPosition(const int x, const int y)
{
    rel_position.x = x;
    rel_position.y = y;
}

void Collider2D::SetDimensions(const int w, const int h)
{
    colliderRect.w = w;
    colliderRect.h = h;
}

void Collider2D::SetParentPosition(const int x, const int y)
{
    parent_position.x = x;
    parent_position.y = y;
}

void Collider2D::Update(double deltaTime)
{
    colliderRect.x = parent_position.x + rel_position.x;
    colliderRect.y = parent_position.y + rel_position.y;
}

void Collider2D::Render(SDL2pp::Renderer &renderer) const
{
    renderer.SetDrawColor(255, 255, 0, SDL_ALPHA_OPAQUE);
    renderer.DrawRect(colliderRect);
}
