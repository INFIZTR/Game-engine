#include <string>
#include <unordered_map>
#include <iostream>
#include "../include/ResourceManager.hpp"

// Initialize our static member variable.
ResourceManager *ResourceManager::mInstance = nullptr;

/**
 * @brief A custom deleter functor for SDL_Texture.
 *
 * This functor ensures that SDL_DestroyTexture is called when the shared pointer
 * managing an SDL_Texture goes out of scope.
 */
struct TextureFunctorDeleter
{
    void operator()(SDL_Texture *texture) const
    {
        SDL_DestroyTexture(texture);
    }
};

/**
 * @brief Creates a shared pointer to an SDL_Texture from an SDL_Surface.
 *
 * Creates an SDL_Texture from the given surface and returns it as a shared pointer
 * with a custom deleter (TextureFunctorDeleter). If texture creation fails, returns nullptr.
 *
 * @param renderer The SDL_Renderer used to create the texture.
 * @param pixels The SDL_Surface containing the image data.
 * @return std::shared_ptr<SDL_Texture> The shared pointer managing the created texture.
 */
std::shared_ptr<SDL_Texture> ResourceManager::make_shared_texture(SDL_Renderer *renderer, SDL_Surface *pixels)
{
    SDL_Texture *pTexture = SDL_CreateTextureFromSurface(renderer, pixels);

    if (pTexture == nullptr)
    {
        SDL_Log("Could not load texture from surface.");
    }

    return std::shared_ptr<SDL_Texture>(pTexture, TextureFunctorDeleter());
}

/**
 * @brief Loads a texture from a BMP file.
 *
 * Checks if the texture specified by filePath is already loaded in the cache.
 * If it is, the cached texture is returned. Otherwise, the BMP is loaded from file,
 * a texture is created, stored in the cache, and then returned.
 *
 * @param filePath The file path to the BMP image.
 * @param renderer The SDL_Renderer used to create the texture.
 * @return std::shared_ptr<SDL_Texture> The shared pointer to the loaded texture, or nullptr on error.
 */
std::shared_ptr<SDL_Texture> ResourceManager::LoadTexture(SDL_Renderer *renderer, std::string filePath)
{
    std::cout << "File Path in Load Texture" << filePath << std::endl;
    // Check if texture is already loaded
    if (mTextures.find(filePath) != mTextures.end())
    {
        std::cout << "Reusing Texture: " << mTextures[filePath].get() << std::endl;
        return mTextures[filePath];
    }

    // Load BMP file
    SDL_Surface *pixels = SDL_LoadBMP(filePath.c_str());
    if (!pixels)
    {
        SDL_Log("Failed to load image: %s", SDL_GetError());
        return nullptr;
    }

    std::shared_ptr<SDL_Texture> texture = make_shared_texture(renderer, pixels);
    mTextures[filePath] = texture;
    SDL_FreeSurface(pixels); // Free the surface as it's no longer needed
    std::cout << "Creating New Texture: " << mTextures[filePath].get() << std::endl;

    return texture;
}
