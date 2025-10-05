#ifndef COLLISION2DCOMPONENT_HPP
#define COLLISION2DCOMPONENT_HPP

#include "../include/Component.hpp"
#include "../include/ComponentType.hpp"
#include <SDL2/SDL.h>
#include <memory>

/**
 * @brief The Collision2DComponent class provides a 2D collision detection rectangle for game entities.
 *
 * This component maintains a SDL_FRect that represents the collision boundary of the entity.
 * The rectangle is updated based on the entity's TransformComponent data.
 */
class Collision2DComponent : public Component
{
public:
    Collision2DComponent();
    Collision2DComponent(float x, float y, float w, float h);
    virtual ~Collision2DComponent() = default;

    /**
     * @brief Sets the x-coordinate of the collision rectangle.
     *
     * @param x The new x-coordinate.
     */
    void setX(float x) { mRectangle.x = x; }

    /**
     * @brief Sets the y-coordinate of the collision rectangle.
     *
     * @param y The new y-coordinate.
     */
    void setY(float y) { mRectangle.y = y; }

    /**
     * @brief Gets the x-coordinate of the collision rectangle.
     *
     * @return float The current x-coordinate.
     */
    float getX() const { return mRectangle.x; }

    /**
     * @brief Gets the y-coordinate of the collision rectangle.
     *
     * @return float The current y-coordinate.
     */
    float getY() const { return mRectangle.y; }

    /**
     * @brief Sets the width of the collision rectangle.
     *
     * @param w The new width.
     */
    void setW(float w) { mRectangle.w = w; }

    /**
     * @brief Sets the height of the collision rectangle.
     *
     * @param h The new height.
     */
    void setH(float h) { mRectangle.h = h; }

    /**
     * @brief Gets the width of the collision rectangle.
     *
     * @return float The current width.
     */
    float getW() const { return mRectangle.w; }

    /**
     * @brief Gets the height of the collision rectangle.
     *
     * @return float The current height.
     */
    float getH() const { return mRectangle.h; }

    /**
     * @brief Retrieves the current collision rectangle.
     *
     * @return SDL_FRect The collision rectangle.
     */
    SDL_FRect getRectangle() const { return mRectangle; }

    virtual void Update(float deltaTime) override;
    virtual void Render(SDL_Renderer *renderer) override;

    /**
     * @brief Returns the component type identifier.
     *
     * @return ComponentType The type of this component.
     */
    virtual ComponentType GetType() const override { return ComponentType::Collision2DComponent; }

    /**
     * @brief Sets the game entity that owns this component.
     *
     * @param entity Shared pointer to the game entity.
     */
    virtual void SetGameEntity(std::shared_ptr<GameEntity> entity) override { mGameEntity = entity; }

    /**
     * @brief Gets the game entity that owns this component.
     *
     * @return std::shared_ptr<GameEntity> The owning game entity.
     */
    virtual std::shared_ptr<GameEntity> GetGameEntity() const override { return mGameEntity; }

private:
    SDL_FRect mRectangle;
    std::shared_ptr<GameEntity> mGameEntity;
};

#endif
