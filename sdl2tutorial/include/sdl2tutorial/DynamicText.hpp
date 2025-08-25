#pragma once

#include <SDL2pp/SDL2pp.hh>


class DynamicText
{
public:

    DynamicText(const std::string &filepath, int font_size);

    void SetText(SDL2pp::Renderer &renderer, const std::string &new_text, SDL2pp::Color color);
    void SetPosition(SDL2pp::Rect position);
    void Render(SDL2pp::Renderer &renderer) const;

private:

    SDL2pp::Font m_font;
    std::unique_ptr<SDL2pp::Texture> m_texture;
    SDL2pp::Rect m_position{};
};
