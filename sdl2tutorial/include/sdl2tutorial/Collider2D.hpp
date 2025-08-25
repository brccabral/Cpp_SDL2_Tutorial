#pragma once
#include <SDL2pp/SDL2pp.hh>


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
    void Render(SDL2pp::Renderer &renderer) const;

private:

    SDL2pp::Point parent_position{};
    SDL2pp::Point rel_position{};
    SDL2pp::Rect colliderRect{};
};
