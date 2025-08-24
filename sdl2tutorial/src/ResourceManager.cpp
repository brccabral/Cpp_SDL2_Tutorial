#include <sdl2tutorial/ResourceManager.h>

ResourceManager::ResourceManager()
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
