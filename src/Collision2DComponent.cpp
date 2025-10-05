#include "Collision2DComponent.h"
#include "TransformComponent.h"
#include "../src/GameEntity.h"
#include <iostream>

/**
 * @brief Default constructor.
 *
 * Initializes the collision rectangle to (0, 0, 0, 0).
 */
Collision2DComponent::Collision2DComponent() : mRectangle{0, 0, 0, 0} {}

/**
 * @brief Parameterized constructor.
 *
 * Initializes the collision rectangle with the given parameters.
 *
 * @param x The x-coordinate of the rectangle.
 * @param y The y-coordinate of the rectangle.
 * @param w The width of the rectangle.
 * @param h The height of the rectangle.
 */
Collision2DComponent::Collision2DComponent(float x, float y, float w, float h)
    : mRectangle{x, y, w, h} {}

/**
 * @brief Updates the collision rectangle.
 *
 * Retrieves the game entity's TransformComponent and updates the collision rectangle
 * to match the transform's rectangle.
 *
 * @param deltaTime The time elapsed since the last update in seconds.
 */
void Collision2DComponent::Update(float deltaTime)
{
    auto entity = GetGameEntity();
    if (entity)
    {
        auto transform = entity->GetComponent<TransformComponent>(ComponentType::TransformComponent);
        if (transform)
        {
            mRectangle = transform->getRectangle();
        }
    }
}

/**
 * @brief Renders the collision rectangle.
 *
 * For debugging purposes, sets the drawing color to red and draws the collision rectangle.
 *
 * @param renderer The SDL_Renderer used for drawing.
 */
void Collision2DComponent::Render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRectF(renderer, &mRectangle);
}
