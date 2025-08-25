#pragma once
#include <string>
#include <SDL2pp/SDL2pp.hh>


class Sound
{
public:

    explicit Sound(const std::string &filepath);
    Sound(const Sound &other) = delete;
    Sound &operator=(const Sound &other) = delete;
    Sound(Sound &&other) noexcept;
    Sound &operator=(Sound &&other) noexcept;
    void Play(SDL2pp::AudioDevice &audio_device);
    void Stop(SDL2pp::AudioDevice &audio_device);

private:

    SDL2pp::Wav m_wav;
    SDL2pp::AudioSpec m_spec; // must be declared after m_wav
};
