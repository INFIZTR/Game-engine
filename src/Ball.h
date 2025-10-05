#ifndef BALL_H
#define BALL_H

#include "GameEntity.h"

/**
 * @brief The Ball class represents the ball in the game.
 *
 * It inherits from GameEntity and handles its own motion, collision with screen boundaries and velocity updates.
 */
class Ball : public GameEntity
{
public:
    Ball(SDL_Renderer *renderer, const char *texturePath, float speed);
    virtual void Update(float deltaTime) override;
    void SetVelocity(float vx, float vy);

    /**
     * @brief Reverses the horizontal velocity of the ball.
     */
    void ReverseVelX() { velX = -velX; }

    /**
     * @brief Reverses the vertical velocity of the ball.
     */
    void ReverseVelY() { velY = -velY; }

    /**
     * @brief Gets the horizontal velocity of the ball.
     *
     * @return float The horizontal velocity.
     */
    float GetVelX() const { return velX; }

    /**
     * @brief Gets the vertical velocity of the ball.
     *
     * @return float The vertical velocity.
     */
    float GetVelY() const { return velY; }

private:
    float velX;
    float velY;
};

#endif
