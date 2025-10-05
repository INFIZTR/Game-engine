#include "Paddle.h"
#include "TransformComponent.h"
#include "InputComponent.h"
#include "../include/ComponentType.hpp"
#include <SDL2/SDL.h>

/**
 * @brief Constructs a new Paddle object.
 *
 * Calls the base GameEntity constructor.
 *
 * @param renderer The SDL_Renderer used for creating components.
 * @param texturePath The path to the paddle texture.
 * @param speed The paddle's movement speed.
 */
Paddle::Paddle(SDL_Renderer *renderer, const char *texturePath, float speed)
    : GameEntity(renderer, texturePath, speed)
{
}

/**
 * @brief Processes input for the paddle.
 *
 * Retrieves the InputComponent and delegates the input processing.
 *
 * @param deltaTime The time elapsed since the last frame in seconds.
 */
void Paddle::Input(float deltaTime)
{
    auto inputComp = GetComponent<InputComponent>(ComponentType::InputComponent);
    if (inputComp)
    {
        inputComp->Input(deltaTime);
    }
}

/**
 * @brief Updates the paddle.
 *
 * Calculates the instantaneous horizontal velocity based on current and last x positions,
 * then updates the collision component to synchronize with the current transform.
 *
 * @param deltaTime The time elapsed since the last frame in seconds.
 */
void Paddle::Update(float deltaTime)
{
    auto trans = GetComponent<TransformComponent>(ComponentType::TransformComponent);
    if (trans)
    {
        float currentX = trans->getX();
        instantaneousVelocity = (currentX - lastPosX) / deltaTime;
        lastPosX = currentX;
    }

    auto coll = GetComponent<Collision2DComponent>(ComponentType::Collision2DComponent);
    if (coll)
    {
        coll->Update(deltaTime);
    }
}
