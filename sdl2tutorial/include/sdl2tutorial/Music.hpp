#pragma once

#include <SDL2pp/SDL2pp.hh>

class Music
{
public:

    explicit Music(const std::string &filepath);

    // loops: 0 = never, -1 = forever
    void Play(int loops) const;

private:

    SDL2pp::Music m_music;
};
