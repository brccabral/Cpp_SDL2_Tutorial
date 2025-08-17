#include "DynamicText.hpp"
#include <SDL_ttf.h>


DynamicText::DynamicText(const std::string &filepath, const int font_size)
{
    m_font = TTF_OpenFont(filepath.c_str(), font_size);
    if (m_font == nullptr)
    {
        fprintf(stderr, "TTF_OpenFont: %s\n", TTF_GetError());
    }
}

DynamicText::~DynamicText()
{
    SDL_DestroyTexture(m_texture);
    TTF_CloseFont(m_font);
}

void DynamicText::SetText(
        SDL_Renderer *renderer, const std::string &new_text, const SDL_Color color)
{
    SDL_Surface *surfaceText = TTF_RenderText_Solid(m_font, new_text.c_str(), color);
    m_texture = SDL_CreateTextureFromSurface(renderer, surfaceText);
    SDL_FreeSurface(surfaceText);
}

void DynamicText::SetPosition(const SDL_Rect position)
{
    m_position = position;
}

void DynamicText::Render(SDL_Renderer *renderer) const
{

    SDL_RenderCopy(renderer, m_texture, nullptr, &m_position);
}
