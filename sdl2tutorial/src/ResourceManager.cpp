#include <sdl2tutorial/ResourceManager.h>

ResourceManager::ResourceManager()
    : m_mixer(
              MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096,
              SDL2pp::NullOpt,
              SDL_AUDIO_ALLOW_ANY_CHANGE),
      m_audio_device(
              SDL2pp::NullOpt, false,
              {MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096})
{
}

void ResourceManager::Destroy()
{
    instance.reset();
}

ResourceManager &ResourceManager::GetInstance()
{
    if (!instance)
    {
        instance.reset(new ResourceManager());
    }
    return *instance;
}

SDL2pp::Surface &ResourceManager::GetSurface(const std::string &filepath)
{
    const auto search = surfaces.find(filepath);
    if (search != surfaces.end())
    {
        return search->second;
    }
    surfaces.emplace(filepath, filepath.c_str());
    return surfaces.at(filepath);
}

void ResourceManager::SetMixerDevice(const SDL2pp::Optional<std::string> &device)
{
    m_mixer.CloseAudio();
    m_mixer = SDL2pp::Mixer(
            MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096, device,
            SDL_AUDIO_ALLOW_ANY_CHANGE);
}

SDL2pp::Mixer &ResourceManager::GetMixer()
{
    return m_mixer;
}

void ResourceManager::SetAudioDevice(const SDL2pp::Optional<std::string> &device)
{
    m_audio_device = SDL2pp::AudioDevice(
            device, false, {MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096});
}

SDL2pp::AudioDevice &ResourceManager::GetAudioDevice()
{
    return m_audio_device;
}
