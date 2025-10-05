#include "Brick.h"
#include "TransformComponent.h"
#include "../include/ComponentType.hpp"
#include <SDL2/SDL.h>

/**
 * @brief Constructs a new Brick object.
 *
 * Initializes the brick by calling the base GameEntity constructor and sets the brick to active.
 *
 * @param renderer The SDL_Renderer used for texture creation.
 * @param texturePath The path to the brick texture file.
 * @param speed The base speed value for the brick (default is 0.0f).
 */
Brick::Brick(SDL_Renderer *renderer, const char *texturePath, float speed)
    : GameEntity(renderer, texturePath, speed), active(true)
{
}

/**
 * @brief Renders the brick.
 *
 * Only renders the brick if it is active.
 *
 * @param renderer The SDL_Renderer used for drawing the brick.
 */
void Brick::Render(SDL_Renderer *renderer)
{
    if (!active)
        return;
    GameEntity::Render(renderer);
}

/**
 * @brief Updates the brick.
 *
 * Updates the brick's collision component (Collision2DComponent) so that its collision rectangle stays synchronized with the brick's transform.
 *
 * @param deltaTime The elapsed time since the last frame in seconds.
 */
void Brick::Update(float deltaTime)
{
    auto coll = GetComponent<Collision2DComponent>(ComponentType::Collision2DComponent);
    if (coll)
    {
        coll->Update(deltaTime);
    }
}