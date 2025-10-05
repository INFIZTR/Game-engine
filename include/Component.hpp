#pragma once
#include <SDL2/SDL.h>
#include "ComponentType.hpp"
#include <memory>

class GameEntity;

class Component
{
public:
    virtual ~Component() {}
    virtual void Input(float deltaTime) {}
    virtual void Update(float deltaTime) {}
    virtual void Render(SDL_Renderer *renderer) {}
    virtual ComponentType GetType() const = 0;

    virtual void SetGameEntity(std::shared_ptr<GameEntity> entity) {}
    virtual std::shared_ptr<GameEntity> GetGameEntity() const { return nullptr; }
};
