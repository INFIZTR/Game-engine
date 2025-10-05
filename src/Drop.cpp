#include "Drop.h"
#include "TransformComponent.h"
#include "../include/ComponentType.hpp"
#include <SDL2/SDL.h>

/**
 * @brief Constructs a new Drop object.
 *
 * Initializes the Drop object by calling the base GameEntity constructor.
 * Note: initComponents() should be called externally after the Drop object is created.
 *
 * @param renderer The SDL_Renderer used for texture creation.
 * @param texturePath The file path to the drop's BMP texture.
 * @param speed The vertical falling speed (in pixels per second).
 */
Drop::Drop(SDL_Renderer *renderer, const char *texturePath, float speed)
    : GameEntity(renderer, texturePath, speed)
{
}

/**
 * @brief Updates the drop's state.
 *
 * This function updates the vertical position of the drop by moving it downward according to
 * its speed and the elapsed time. It then updates the drop's collision component.
 *
 * @param deltaTime The time elapsed since the last frame (in seconds).
 */
void Drop::Update(float deltaTime)
{
    auto trans = GetComponent<TransformComponent>(ComponentType::TransformComponent);
    if (!trans)
        return;
    float x = trans->getX();
    float y = trans->getY();
    y += mSpeed * deltaTime;
    trans->move(x, y);

    auto coll = GetComponent<Collision2DComponent>(ComponentType::Collision2DComponent);
    if (coll)
        coll->Update(deltaTime);
}
