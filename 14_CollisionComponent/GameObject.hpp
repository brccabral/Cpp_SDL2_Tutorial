#pragma once

#include <vector>
#include <SDL2/SDL.h>

#include "Collider2D.hpp"
#include "TextureRectangle.h"

class GameObject
{
public:

    GameObject();
    explicit GameObject(SDL_Renderer *renderer);
    ~GameObject();

    void Update(double deltaTime);
    void Render() const;

    void SetTextureRect(const std::string &sprite_path);
    void SetTextureRect(
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
    SDL_Renderer *m_renderer{};
    // Collider2D m_collider{};
    std::vector<Collider2D> m_colliders{};
};
