#include <sdl2tutorial/Music.hpp>
#include <sdl2tutorial/ResourceManager.h>


Music::Music(const std::string &filepath)
    : m_music(filepath)
{
}

void Music::Play(const int loops) const
{
    ResourceManager::GetInstance().GetMixer().PlayMusic(m_music, loops);
}
