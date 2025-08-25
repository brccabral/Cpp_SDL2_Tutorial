#include <string>
#include <sdl2tutorial/Sound.hpp>

Sound::Sound(const std::string &filepath, const SDL2pp::Optional<std::string> &device)
    : m_wav(filepath),
      m_spec(
              m_wav.GetSpec().freq, m_wav.GetSpec().format, m_wav.GetSpec().channels,
              m_wav.GetSpec().samples),
      m_audio_device(device, false, m_spec, SDL_AUDIO_ALLOW_ANY_CHANGE)
{
}

Sound::Sound(Sound &&other) noexcept = default;

Sound &Sound::operator=(Sound &&other) noexcept = default;

void Sound::Play()
{
    m_audio_device.QueueAudio(m_wav.GetBuffer(), m_wav.GetLength());
    m_audio_device.Pause(false);
}

void Sound::Stop()
{
    m_audio_device.Pause(true);
}
