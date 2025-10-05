#pragma once

#include "SDL2/SDL.h"
#include "../include/ResourceManager.hpp"
#include <string>

class Sprite {
    public:
        Sprite();
        ~Sprite();

        /**
         * @brief Creates a sprite by loading a texture from a file.
         * 
         * This function utilizes the ResourceManager to load the texture
         * from the given file path and stores it in the sprite's texture member.
         * 
         * @param renderer The SDL_Renderer used to create and render the texture.
         * @param filePath The file path to the image file to be used for the sprite.
         */
        void CreateSprite(SDL_Renderer* renderer, std::string filePath);

        /**
         * @brief Renders the sprite on the screen.
         * 
         * If a texture is available, it is drawn using SDL_RenderCopyF.
         * Otherwise, a simple rectangle is drawn as a placeholder.
         * 
         * @param renderer The SDL_Renderer used to render the sprite.
         */
        void Render(SDL_Renderer* renderer);

        void Move(float x, float y);
        void SetX(float x);
        void SetY(float y);
        float GetX() const;
        float GetY() const;
        void SetW(int w);
        void SetH(int h);
        SDL_FRect getRectangle();

    private:
        SDL_FRect mRectangle{40.0f, 40.0f, 40.0f, 40.0f};
        std::shared_ptr<SDL_Texture> mTexture;
};