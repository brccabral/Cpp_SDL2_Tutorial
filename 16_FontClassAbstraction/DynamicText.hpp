#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>


class DynamicText
{
public:

    DynamicText() = default;
    DynamicText(const std::string &filepath, int font_size);
    ~DynamicText();

    void SetText(SDL_Renderer *renderer, const std::string &new_text, SDL_Color color);
    void SetPosition(SDL_Rect position);
    void Render(SDL_Renderer *renderer) const;

private:

    TTF_Font *m_font = nullptr;
    SDL_Texture *m_texture = nullptr;
    SDL_Rect m_position{};
};
