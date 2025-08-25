#include <string>
#include <sdl2tutorial/Sound.hpp>

Sound::Sound(const std::string &filepath)
    : m_wav(filepath),
      m_spec(
              m_wav.GetSpec().freq, m_wav.GetSpec().format, m_wav.GetSpec().channels,
              m_wav.GetSpec().samples)
{
}

Sound::Sound(Sound &&other) noexcept = default;

Sound &Sound::operator=(Sound &&other) noexcept = default;

void Sound::Play(SDL2pp::AudioDevice &audio_device)
{
    audio_device.QueueAudio(m_wav.GetBuffer(), m_wav.GetLength());
    audio_device.Pause(false);
}

void Sound::Stop(SDL2pp::AudioDevice &audio_device)
{
    audio_device.Pause(true);
}
