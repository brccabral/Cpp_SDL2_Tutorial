#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
    for (auto &[filepath, surface]: surfaces)
    {
        SDL_FreeSurface(surface);
    }
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

SDL_Surface *ResourceManager::GetSurface(const std::string &filepath)
{
    const auto search = surfaces.find(filepath);
    if (search != surfaces.end())
    {
        return search->second;
    }
    SDL_Surface *surface = SDL_LoadBMP(filepath.c_str());
    if (surface == nullptr)
    {
        fprintf(stderr, "SDL_LoadBMP Error: %s\n", SDL_GetError());
        return nullptr;
    }
    surfaces[filepath] = surface;
    return surface;
}
