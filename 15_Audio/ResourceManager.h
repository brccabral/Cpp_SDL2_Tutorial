#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <SDL2/SDL.h>


class ResourceManager
{
private:

    ResourceManager();
    ResourceManager(ResourceManager const &) = delete;
    ResourceManager &operator=(ResourceManager const &) = delete;

    inline static std::unique_ptr<ResourceManager> instance;

    std::unordered_map<std::string, SDL_Surface *> surfaces;

public:

    ~ResourceManager();
    static void Destroy();
    static ResourceManager &GetInstance();

    SDL_Surface *GetSurface(const std::string &filepath);
};
