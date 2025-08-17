#pragma once
#include <SDL_audio.h>
#include <string>


class Sound
{
public:

    Sound() = default;
    explicit Sound(const std::string &filepath);
    ~Sound();
    Sound(const Sound &other) = delete;
    Sound(Sound &&other) noexcept;
    Sound &operator=(const Sound &other) = delete;
    Sound &operator=(Sound &&other) noexcept;
    SDL_AudioDeviceID SetupDevice();
    void Play() const;
    void Stop() const;

private:

    SDL_AudioDeviceID m_audio_device{};
    SDL_AudioSpec m_spec{};
    Uint8 *m_buffer = nullptr;
    Uint32 m_buffer_size{};
};
