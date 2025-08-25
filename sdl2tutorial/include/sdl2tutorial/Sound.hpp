#pragma once
#include <string>
#include <SDL2pp/SDL2pp.hh>


class Sound
{
public:

    explicit Sound(const std::string &filepath, const SDL2pp::Optional<std::string> &device);
    Sound(const Sound &other) = delete;
    Sound &operator=(const Sound &other) = delete;
    Sound(Sound &&other) noexcept;
    Sound &operator=(Sound &&other) noexcept;
    void Play();
    void Stop();

private:

    SDL2pp::Wav m_wav;
    SDL2pp::AudioSpec m_spec;
    SDL2pp::AudioDevice m_audio_device;
};
