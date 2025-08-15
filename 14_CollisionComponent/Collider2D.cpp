#include "Collider2D.hpp"

SDL_bool Collider2D::IsColliding(const Collider2D &other) const
{
    return SDL_HasIntersection(&colliderRect, &other.colliderRect);
}

void Collider2D::SetAbsolutePosition(const int &x, const int &y)
{
    colliderRect.x = x;
    colliderRect.y = y;
}

void Collider2D::SetDimensions(const int &w, const int &h)
{
    colliderRect.w = w;
    colliderRect.h = h;
}

void Collider2D::Render(SDL_Renderer *renderer) const
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &colliderRect);
}
