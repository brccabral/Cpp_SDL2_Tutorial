#include "Sound.hpp"

Sound::Sound(const std::string &filepath)
{
    if (SDL_LoadWAV(filepath.c_str(), &m_spec, &m_buffer, &m_buffer_size) == nullptr)
    {
        fprintf(stderr, "SDL_LoadWAV Error: %s\n", SDL_GetError());
    }
}

Sound::~Sound()
{
    SDL_FreeWAV(m_buffer);
    if (m_audio_device)
    {
        SDL_CloseAudioDevice(m_audio_device);
    }
}

Sound::Sound(Sound &&other) noexcept
{
    m_audio_device = other.m_audio_device;
    m_buffer_size = other.m_buffer_size;
    m_buffer = other.m_buffer;
    m_spec = other.m_spec;
    other.m_buffer = nullptr;
    other.m_audio_device = 0;
}

Sound &Sound::operator=(Sound &&other) noexcept
{
    m_audio_device = other.m_audio_device;
    m_buffer_size = other.m_buffer_size;
    m_buffer = other.m_buffer;
    m_spec = other.m_spec;
    other.m_buffer = nullptr;
    other.m_audio_device = 0;
    return *this;
}

SDL_AudioDeviceID Sound::SetupDevice()
{
    m_audio_device = SDL_OpenAudioDevice(nullptr, 0, &m_spec, nullptr, SDL_AUDIO_ALLOW_ANY_CHANGE);
    if (0 == m_audio_device)
    {
        fprintf(stderr, "SDL_OpenAudioDevice Error: %s\n", SDL_GetError());
    }
    return m_audio_device;
}

void Sound::Play() const
{
    const int status = SDL_QueueAudio(m_audio_device, m_buffer, m_buffer_size);
    if (status < 0)
    {
        fprintf(stderr, "SDL_QueueAudio Error: %s\n", SDL_GetError());
        return;
    }
    SDL_PauseAudioDevice(m_audio_device, 0);
}

void Sound::Stop() const
{
    SDL_PauseAudioDevice(m_audio_device, 1);
}
