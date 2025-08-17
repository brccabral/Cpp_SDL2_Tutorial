#pragma once

#include <string>
#include <SDL2/SDL_mixer.h>

class Music
{
public:

    Music() = default;
    explicit Music(const std::string &filepath);
    ~Music();

    // loops: 0 = never, -1 = forever
    void Play(int loops) const;

private:

    Mix_Music *m_music = nullptr;
};
