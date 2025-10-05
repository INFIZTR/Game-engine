#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include "../include/Component.hpp"
#include "../include/ComponentType.hpp"
#include <SDL2/SDL.h>
#include <memory>

/**
 * @brief The TransformComponent class provides position and size data for a game entity.
 *
 * This component holds an SDL_FRect that represents the position (x, y) and dimensions (width, height)
 * of the entity. It is used for rendering and collision detection.
 */
class TransformComponent : public Component
{
public:
    TransformComponent();
    TransformComponent(float x, float y, float w, float h);
    virtual ~TransformComponent() = default;

    /**
     * @brief Sets the x-coordinate of the rectangle.
     *
     * @param x The new x-coordinate.
     */
    void setX(float x) { mRectangle.x = x; }

    /**
     * @brief Sets the y-coordinate of the rectangle.
     *
     * @param y The new y-coordinate.
     */
    void setY(float y) { mRectangle.y = y; }

    /**
     * @brief Gets the x-coordinate of the rectangle.
     *
     * @return float The current x-coordinate.
     */
    float getX() const { return mRectangle.x; }

    /**
     * @brief Gets the y-coordinate of the rectangle.
     *
     * @return float The current y-coordinate.
     */
    float getY() const { return mRectangle.y; }

    /**
     * @brief Sets the width of the rectangle.
     *
     * @param w The new width.
     */
    void setW(float w) { mRectangle.w = w; }

    /**
     * @brief Sets the height of the rectangle.
     *
     * @param h The new height.
     */
    void setH(float h) { mRectangle.h = h; }

    /**
     * @brief Gets the width of the rectangle.
     *
     * @return float The current width.
     */
    float getW() const { return mRectangle.w; }

    /**
     * @brief Gets the height of the rectangle.
     *
     * @return float The current height.
     */
    float getH() const { return mRectangle.h; }

    SDL_FRect getRectangle();

    void move(float x, float y);

    virtual void Input(float deltaTime) override {}
    virtual void Update(float deltaTime) override {}
    virtual void Render(SDL_Renderer *renderer) override
    {
    }

    /**
     * @brief Retrieves the component type.
     *
     * @return ComponentType Returns ComponentType::TransformComponent.
     */
    virtual ComponentType GetType() const override { return ComponentType::TransformComponent; }

private:
    SDL_FRect mRectangle;
};

#endif
