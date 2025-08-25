#pragma once
#include <memory>
#include <string>
#include <unordered_map>

#include <SDL2pp/SDL2pp.hh>


class ResourceManager
{
private:

    ResourceManager();

    inline static std::unique_ptr<ResourceManager> instance;

    std::unordered_map<std::string, SDL2pp::Surface> surfaces;
    SDL2pp::Mixer m_mixer;
    SDL2pp::AudioDevice m_audio_device;

public:

    ResourceManager(ResourceManager const &) = delete;
    ResourceManager &operator=(ResourceManager const &) = delete;

    static void Destroy();
    static ResourceManager &GetInstance();

    SDL2pp::Surface &GetSurface(const std::string &filepath);

    void SetMixerDevice(const SDL2pp::Optional<std::string> &device);
    SDL2pp::Mixer &GetMixer();

    void SetAudioDevice(const SDL2pp::Optional<std::string> &device);
    SDL2pp::AudioDevice &GetAudioDevice();
};
