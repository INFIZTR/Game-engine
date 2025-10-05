#pragma once
#include "SDL2/SDL.h"
#include "../include/ResourceManager.hpp"
#include "../include/Component.hpp"
#include <string>

class TextureComponent : public Component
{
public:
    TextureComponent();
    ~TextureComponent();

    /**
     * @brief Creates a texture component by loading a texture from a file.
     *
     * This function utilizes the ResourceManager to load the texture
     * from the given file path.
     *
     * @param renderer The SDL_Renderer used to create and render the texture.
     * @param filePath The file path to the image file to be used texture.
     */
    void CreateTextureComponent(SDL_Renderer *renderer, std::string filePath);

    /**
     * @brief Retrieves the type identifier for the TextureComponent.
     *
     * This function returns the component type associated with TextureComponent.
     * It is used to identify the component in the entity-component system.
     *
     * @return ComponentType The type identifier for TextureComponent.
     */
    ComponentType GetType() override;

    void Input(float deltaTime) override {}

    void Update(float deltaTime) override {}

    /**
     * @brief Renders the sprite on the screen.
     *
     * If a texture is available, it is drawn using SDL_RenderCopyF.
     * Otherwise, a simple rectangle is drawn as a placeholder.
     *
     * @param renderer The SDL_Renderer used to render the sprite.
     */
    void Render(SDL_Renderer *renderer) override;

    void Move(float x, float y);
    void SetX(float x);
    void SetY(float y);
    float getX() const;
    float getY() const;
    void SetW(int w);
    void SetH(int h);
    SDL_FRect getRectangle();

private:
    SDL_FRect mRectangle{40.0f, 40.0f, 40.0f, 40.0f};
    std::shared_ptr<SDL_Texture> mTexture;
};