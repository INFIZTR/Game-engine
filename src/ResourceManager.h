#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <unordered_map>
#include <memory>
#include <string>
#include <SDL2/SDL.h>

/**
 * @brief The ResourceManager class manages game resources, such as textures.
 *
 * This singleton class loads BMP textures via SDL and caches them to avoid
 * duplicate loading. It returns shared pointers to SDL_Texture objects that are
 * automatically freed when no longer needed.
 */
class ResourceManager
{
public:
    /**
     * @brief Returns the singleton instance of ResourceManager.
     *
     * Uses the Meyers' singleton pattern.
     *
     * @return ResourceManager& A reference to the singleton instance.
     */
    static ResourceManager &getInstance()
    {
        static ResourceManager instance;
        return instance;
    }

    std::shared_ptr<SDL_Texture> LoadTexture(const std::string &filePath, SDL_Renderer *renderer);

private:
    ResourceManager() = default;
    ~ResourceManager() = default;
    ResourceManager(const ResourceManager &) = delete;
    ResourceManager &operator=(const ResourceManager &) = delete;

    std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> textures;
};

#endif
