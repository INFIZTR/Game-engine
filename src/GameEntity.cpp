#include <memory>
#include "GameEntity.h"
#include <iostream>
#include <ostream>

/**
 * @brief Constructs a new GameEntity object.
 *
 * Initializes speed, movement direction, and renderable status.
 *
 * @param renderer The SDL_Renderer used for component initialization.
 * @param texturePath The path to the entity's texture.
 * @param speed The base speed for the entity.
 */
GameEntity::GameEntity(SDL_Renderer *renderer, const char *texturePath, float speed)
    : mSpeed(speed), xPositiveDirection(1), renderable(true)
{
}

/**
 * @brief Tests collision between this entity and another.
 *
 * Compares the collision rectangles retrieved from each entity's Collision2DComponent.
 *
 * @param other A shared pointer to the other GameEntity.
 * @return true if the collision rectangles intersect, false otherwise.
 */
bool GameEntity::TestCollision(std::shared_ptr<GameEntity> otherRect)
{
    auto collThis = GetComponent<Collision2DComponent>(ComponentType::Collision2DComponent);
    auto collOther = otherRect->GetComponent<Collision2DComponent>(ComponentType::Collision2DComponent);
    if (!collThis || !collOther)
        return false;

    SDL_FRect thisRect = collThis->getRectangle();
    SDL_FRect thatRect = collOther->getRectangle();

    return !(thatRect.x + thatRect.w <= thisRect.x ||
             thisRect.x + thisRect.w <= thatRect.x ||
             thatRect.y + thatRect.h <= thisRect.y ||
             thisRect.y + thisRect.h <= thatRect.y);
}

/**
 * @brief Updates the game entity.
 *
 * First, updates the TransformComponent by moving the entity horizontally according
 * to mSpeed and xPositiveDirection. Then, updates the Collision2DComponent so that its
 * collision rectangle remains synchronized with the transform.
 *
 * @param deltaTime The time elapsed since the last frame in seconds.
 */
void GameEntity::Update(float deltaTime)
{
    auto tex = GetComponent<TransformComponent>(ComponentType::TransformComponent);
    if (tex)
    {
        float newX = tex->getX() + xPositiveDirection * mSpeed * deltaTime;
        tex->move(newX, tex->getY());
    }

    auto coll = GetComponent<Collision2DComponent>(ComponentType::Collision2DComponent);
    if (coll)
    {
        coll->Update(deltaTime);
    }
}

/**
 * @brief Renders the game entity.
 *
 * Uses the TextureComponent and TransformComponent to render the entity. Also,
 * for debugging purposes, renders the collision rectangle using the Collision2DComponent.
 *
 * @param renderer The SDL_Renderer used for drawing.
 */
void GameEntity::Render(SDL_Renderer *renderer)
{
    auto textureComp = GetComponent<TextureComponent>(ComponentType::TextureComponent);
    auto transformComp = GetComponent<TransformComponent>(ComponentType::TransformComponent);
    if (textureComp && transformComp && renderable)
    {
        SDL_FRect rect = transformComp->getRectangle();
        SDL_RenderCopyF(renderer, textureComp->getTexture(), nullptr, &rect);

        auto coll = GetComponent<Collision2DComponent>(ComponentType::Collision2DComponent);
        if (coll)
        {
            coll->Render(renderer);
        }
    }
}

/**
 * @brief Retrieves the x-coordinate of the game entity.
 *
 * Obtains the x-coordinate from the TransformComponent.
 *
 * @return float The x-coordinate, or 0 if unavailable.
 */
float GameEntity::getX() const
{
    auto tex = const_cast<GameEntity *>(this)->GetComponent<TransformComponent>(ComponentType::TransformComponent);
    return tex ? tex->getX() : 0;
}

/**
 * @brief Retrieves the y-coordinate of the game entity.
 *
 * Obtains the y-coordinate from the TransformComponent.
 *
 * @return float The y-coordinate, or 0 if unavailable.
 */
float GameEntity::getY() const
{
    auto tex = const_cast<GameEntity *>(this)->GetComponent<TransformComponent>(ComponentType::TransformComponent);
    return tex ? tex->getY() : 0;
}
