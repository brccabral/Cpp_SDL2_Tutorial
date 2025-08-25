#include <sdl2tutorial/SDL2Tutorial.hpp>


DynamicText::DynamicText(const std::string &filepath, const int font_size)
    : m_font(filepath, font_size)
{
}

void DynamicText::SetText(
        SDL2pp::Renderer &renderer, const std::string &new_text, const SDL2pp::Color color)
{
    SDL2pp::Surface surfaceText = m_font.RenderText_Solid(new_text.c_str(), color);
    m_texture = std::make_unique<SDL2pp::Texture>(renderer, surfaceText);
}

void DynamicText::SetPosition(const SDL2pp::Rect position)
{
    m_position = position;
}

void DynamicText::Render(SDL2pp::Renderer &renderer) const
{
    renderer.Copy(*m_texture, SDL2pp::NullOpt, m_position);
}
