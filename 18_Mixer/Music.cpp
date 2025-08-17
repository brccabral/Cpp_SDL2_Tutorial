#include "Music.hpp"

Music::Music(const std::string &filepath)
{
    m_music = Mix_LoadMUS(filepath.c_str());
    if (m_music == nullptr)
    {
        fprintf(stderr, "Mix_LoadMUS Error: %s\n", Mix_GetError());
    }
}

Music::~Music()
{
    Mix_FreeMusic(m_music);
}

void Music::Play(const int loops) const
{
    if (m_music != nullptr)
    {
        Mix_PlayMusic(m_music, loops);
    }
}
