#include "TextureComponent.h"
#include <iostream>

/**
 * @brief Constructs a new TextureComponent object.
 *
 * Attempts to load a BMP image from texturePath. On success, creates an SDL_Texture from the surface,
 * initializes the destination rectangle with the image dimensions, and frees the surface.
 *
 * @param renderer The SDL_Renderer used to create the texture.
 * @param texturePath The file path to the BMP image.
 */
TextureComponent::TextureComponent(SDL_Renderer *renderer, const char *texturePath)
{
    SDL_Surface *surface = SDL_LoadBMP(texturePath);
    if (!surface)
    {
        std::cerr << "Failed to load image: " << texturePath << " SDL_Error: " << SDL_GetError() << std::endl;
        mTexture = nullptr;
        return;
    }
    mTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!mTexture)
    {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
    }
    mRect.x = 0;
    mRect.y = 0;
    mRect.w = static_cast<float>(surface->w);
    mRect.h = static_cast<float>(surface->h);
    SDL_FreeSurface(surface);
}

/**
 * @brief Destroys the TextureComponent object.
 *
 * Frees the SDL_Texture resource if it exists.
 */
TextureComponent::~TextureComponent()
{
    if (mTexture)
        SDL_DestroyTexture(mTexture);
}

/**
 * @brief Renders the texture.
 *
 * Uses SDL_RenderCopyF to draw the texture onto the renderer using the stored rectangle.
 *
 * @param renderer The SDL_Renderer used for drawing.
 */
void TextureComponent::Render(SDL_Renderer *renderer)
{
    if (mTexture)
    {
        SDL_RenderCopyF(renderer, mTexture, nullptr, &mRect);
    }
}

/**
 * @brief Moves the texture's destination rectangle.
 *
 * Updates the x and y coordinates.
 *
 * @param x The new x-coordinate.
 * @param y The new y-coordinate.
 */
void TextureComponent::move(float x, float y)
{
    mRect.x = x;
    mRect.y = y;
}

/**
 * @brief Gets the current x-coordinate.
 *
 * @return float The x-coordinate.
 */
float TextureComponent::getX() const
{
    return mRect.x;
}

/**
 * @brief Gets the current y-coordinate.
 *
 * @return float The y-coordinate.
 */
float TextureComponent::getY() const
{
    return mRect.y;
}

/**
 * @brief Retrieves the rendering rectangle.
 *
 * @return SDL_FRect The destination rectangle for rendering.
 */
SDL_FRect TextureComponent::getRectangle() const
{
    return mRect;
}
