#ifndef PADDLE_H
#define PADDLE_H

#include "GameEntity.h"

/**
 * @brief The Paddle class represents the player-controlled paddle in the game.
 *
 * The Paddle moves horizontally and is controlled via an InputComponent.
 * It also calculates its instantaneous horizontal velocity for additional feedback.
 */
class Paddle : public GameEntity
{
public:
    Paddle(SDL_Renderer *renderer, const char *texturePath, float speed);
    virtual void Input(float deltaTime) override;
    virtual void Update(float deltaTime) override;

    /**
     * @brief Retrieves the instantaneous horizontal velocity of the paddle.
     *
     * @return float The instantaneous velocity (positive for right, negative for left).
     */
    float GetInstantaneousVelocity() const { return instantaneousVelocity; }

private:
    float lastPosX = 0.0f;
    float instantaneousVelocity = 0.0f;
};

#endif
