#pragma once
#include <SDL2/SDL.h>


class Collider2D
{
public:

    Collider2D() = default;
    ~Collider2D() = default;

    [[nodiscard]] SDL_bool IsColliding(const Collider2D &other) const;

    // Set position within parent
    void SetRelPosition(int x, int y);
    void SetDimensions(int w, int h);
    void SetParentPosition(int x, int y);

    void Update(double deltaTime);
    void Render(SDL_Renderer *renderer) const;

private:

    SDL_Point parent_position{};
    SDL_Point rel_position{};
    SDL_Rect colliderRect{};
};
