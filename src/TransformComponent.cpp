#include "TransformComponent.h"
#include <iostream>
#include <ostream>

/**
 * @brief Constructs a new TransformComponent object with a zero-initialized rectangle.
 */
TransformComponent::TransformComponent() : mRectangle{0, 0, 0, 0} {}

/**
 * @brief Constructs a new TransformComponent object with specified values.
 *
 * @param x The initial x-coordinate.
 * @param y The initial y-coordinate.
 * @param w The initial width.
 * @param h The initial height.
 */
TransformComponent::TransformComponent(float x, float y, float w, float h) : mRectangle{x, y, w, h} {}

/**
 * @brief Moves the transform to the specified position.
 *
 * Updates the internal rectangle's x and y values.
 *
 * @param x The new x-coordinate.
 * @param y The new y-coordinate.
 */
void TransformComponent::move(float x, float y)
{
    mRectangle.x = x;
    mRectangle.y = y;
    // std::cout << "Transform moved to (" << x << ", " << y << ")" << std::endl;
}

/**
 * @brief Retrieves the transform's rectangle.
 *
 * @return SDL_FRect The rectangle representing the current position and size.
 */
SDL_FRect TransformComponent::getRectangle()
{
    return mRectangle;
}