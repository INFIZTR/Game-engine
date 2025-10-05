#pragma once
#include "../include/Component.hpp"
#include "../include/ComponentType.hpp"
#include <SDL2/SDL.h>
#include <memory>

/**
 * @brief InputComponent processes user input and updates the associated GameEntity.
 *
 * This component is designed for entities (such as a Paddle in a brick-breaker game)
 * that require user-controlled horizontal movement. It uses SDL_GetKeyboardState() to
 * detect the left/right arrow keys (or A/D keys) and updates the entity's TransformComponent.
 */
class InputComponent : public Component
{
public:
    InputComponent();
    virtual ~InputComponent() = default;

    virtual void Input(float deltaTime) override;

    /**
     * @brief Retrieves the component type.
     *
     * @return ComponentType Returns ComponentType::InputComponent.
     */
    virtual ComponentType GetType() const override { return ComponentType::InputComponent; }

    void SetGameEntity(std::shared_ptr<GameEntity> entity) override;
    std::shared_ptr<GameEntity> GetGameEntity() const override;

    float mSpeed;

private:
    std::shared_ptr<GameEntity> mGameEntity;

    Uint32 mLastShotTime = 0;
    Uint32 mFireRate = 500;
};
