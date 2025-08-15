#pragma once
#include <SDL2/SDL.h>


class Collider2D
{
public:

    Collider2D() = default;
    ~Collider2D() = default;

    [[nodiscard]] SDL_bool IsColliding(const Collider2D &other) const;

    void SetAbsolutePosition(const int &x, const int &y);
    void SetDimensions(const int &w, const int &h);

private:

    SDL_Rect colliderRect{};
};
