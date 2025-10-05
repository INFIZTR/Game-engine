#include "Ball.h"
#include "TransformComponent.h"
#include "../include/ComponentType.hpp"
#include <SDL2/SDL.h>

/**
 * @brief Constructs a new Ball object.
 *
 * Initializes the ball with the specified base speed and default velocities.
 *
 * @param renderer The SDL_Renderer used for texture creation.
 * @param texturePath The path to the ball texture (BMP format).
 * @param speed The base speed value for the ball.
 */
Ball::Ball(SDL_Renderer *renderer, const char *texturePath, float speed)
    : GameEntity(renderer, texturePath, speed), velX(250.0f), velY(250.0f)
{
}

/**
 * @brief Updates the ball's state.
 *
 * The function retrieves the current position from the TransformComponent, updates the ball's position using the velocity and deltaTime,
 * handles collisions with screen boundaries:
 *  - If the ball hits the top, it reverses vertical direction.
 *  - If it hits the left or right boundaries, it reverses horizontal direction.
 * Finally, it moves the ball to the new position and updates the Collision2DComponent.
 *
 * @param deltaTime The time elapsed since the last frame in seconds.
 */
void Ball::Update(float deltaTime)
{
    auto trans = GetComponent<TransformComponent>(ComponentType::TransformComponent);
    if (!trans)
        return;

    float x = trans->getX();
    float y = trans->getY();
    float w = trans->getW();
    float h = trans->getH();

    x += velX * deltaTime;
    y += velY * deltaTime;

    if (y <= 0)
    {
        y = 0;
        velY = -velY;
    }
    if (x <= 0)
    {
        x = 0;
        velX = -velX;
    }
    if (x + w >= 1600)
    {
        x = 1600 - w;
        velX = -velX;
    }

    trans->move(x, y);

    auto coll = GetComponent<Collision2DComponent>(ComponentType::Collision2DComponent);
    if (coll)
    {
        coll->Update(deltaTime);
    }
}

/**
 * @brief Sets the ball's velocity.
 *
 * Updates the horizontal and vertical speed of the ball.
 *
 * @param vx New horizontal velocity.
 * @param vy New vertical velocity.
 */
void Ball::SetVelocity(float vx, float vy)
{
    velX = vx;
    velY = vy;
}
