#include "InputComponent.h"
#include "GameEntity.h"
#include "Paddle.h"
#include "TransformComponent.h"

/**
 * @brief Processes user input to update the controlled GameEntity's horizontal position.
 *
 * Uses SDL_GetKeyboardState() to detect left (A or Left Arrow) and right (D or Right Arrow) key presses.
 * It then adjusts the x-coordinate of the entity's TransformComponent accordingly.
 * Additionally, if the associated GameEntity is a Paddle, it updates the Paddle's direction.
 *
 * @param deltaTime Time elapsed since the last frame in seconds.
 */
void InputComponent::Input(float deltaTime)
{
    SDL_PumpEvents();
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    if (mGameEntity)
    {
        auto trans = mGameEntity->GetComponent<TransformComponent>(ComponentType::TransformComponent);
        if (trans)
        {
            float posX = trans->getX();
            int dir = 0;
            if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT])
            {
                posX -= mSpeed * deltaTime;
                dir = -1;
            }
            if (keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT])
            {
                posX += mSpeed * deltaTime;
                dir = 1;
            }
            const float windowWidth = 1600.0f;
            float paddleWidth = trans->getW();
            if (posX < 0)
                posX = 0;
            if (posX > windowWidth - paddleWidth)
                posX = windowWidth - paddleWidth;

            trans->move(posX, trans->getY());

            auto paddle = std::dynamic_pointer_cast<Paddle>(mGameEntity);
            if (paddle)
            {
                paddle->SetDirection(dir);
            }
        }
    }
}

/**
 * @brief Sets the GameEntity associated with this InputComponent.
 *
 * @param entity Shared pointer to the GameEntity to control.
 */
void InputComponent::SetGameEntity(std::shared_ptr<GameEntity> entity)
{
    mGameEntity = entity;
}

/**
 * @brief Retrieves the GameEntity associated with this InputComponent.
 *
 * @return std::shared_ptr<GameEntity> Shared pointer to the controlled GameEntity.
 */
std::shared_ptr<GameEntity> InputComponent::GetGameEntity() const
{
    return mGameEntity;
}

/**
 * @brief Constructs a new InputComponent object.
 *
 * Initializes the movement speed to 100.0f pixels per second.
 */
InputComponent::InputComponent() : mSpeed(100.0f) {}
