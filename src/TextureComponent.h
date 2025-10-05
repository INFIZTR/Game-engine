#ifndef TEXTURECOMPONENT_H
#define TEXTURECOMPONENT_H

#include "../include/Component.hpp"
#include "../include/ComponentType.hpp"
#include <SDL2/SDL.h>
#include <memory>
#include <string>

/**
 * @brief The TextureComponent class encapsulates texture handling for a game entity.
 *
 * It loads a BMP image from a given file path using SDL_LoadBMP and creates an SDL_Texture.
 * The texture's rendering parameters are stored in an SDL_FRect. This component is used by
 * GameEntity for rendering the entity's visual appearance.
 */
class TextureComponent : public Component
{
public:
    TextureComponent(SDL_Renderer *renderer, const char *texturePath);
    ~TextureComponent();

    virtual void Render(SDL_Renderer *renderer) override;

    /**
     * @brief Returns the component type.
     *
     * @return ComponentType Returns ComponentType::TextureComponent.
     */
    virtual ComponentType GetType() const override { return ComponentType::TextureComponent; }

    void move(float x, float y);
    float getX() const;
    float getY() const;
    SDL_FRect getRectangle() const;

    /**
     * @brief Retrieves the underlying SDL_Texture.
     *
     * @return SDL_Texture* Pointer to the SDL_Texture.
     */
    SDL_Texture *getTexture() const { return mTexture; }

private:
    SDL_Texture *mTexture;
    SDL_FRect mRect;
};

#endif
