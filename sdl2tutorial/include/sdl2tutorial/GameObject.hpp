#pragma once

#include <sdl2tutorial/SDL2Tutorial.hpp>
#include "TextureRectangle.h"
#include "Collider2D.hpp"

class GameObject
{
public:

    GameObject() = default;

    void Update(double deltaTime);
    void Render(SDL2pp::Renderer &renderer);

    void SetTextureRect(SDL2pp::Renderer &renderer, const std::string &sprite_path);
    void SetTextureRect(
            SDL2pp::Renderer &renderer,
            const std::string &sprite_path, Uint8 redColorKey, Uint8 greenColorKey,
            Uint8 blueColorKey);
    void SetPosition(int x, int y);

    TextureRectangle &GetTextureRectangle();
    Collider2D &GetCollider2D(int index);
    const std::vector<Collider2D> &GetAllColliders() const;
    int AddCollider2D();
    [[nodiscard]] SDL_bool IsColliding(const std::vector<Collider2D> &other_colliders) const;

private:

    TextureRectangle m_sprite{};
    std::vector<Collider2D> m_colliders{};
};
