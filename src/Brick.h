#ifndef BRICK_H
#define BRICK_H

#include "GameEntity.h"

/**
 * @brief The Brick class represents a breakable (or unbreakable) brick in the game.
 *
 * The Brick class inherits from GameEntity and provides functionality for rendering,
 * updating its collision component, and handling its "active" state (i.e. whether it is broken).
 * An unbreakable brick will ignore attempts to set its state to inactive.
 */
class Brick : public GameEntity
{
public:
    Brick(SDL_Renderer *renderer, const char *texturePath, float speed = 0.0f);
    virtual ~Brick() = default;

    virtual void Render(SDL_Renderer *renderer) override;
    virtual void Update(float deltaTime) override;

    /**
     * @brief Checks if the brick is active.
     *
     * @return true if the brick is active, false otherwise.
     */
    bool IsActive() const { return active; }

    /**
     * @brief Sets the brick's active state.
     *
     * For unbreakable bricks, this function does not change the active state.
     *
     * @param a The new active state.
     */
    virtual void SetActive(bool a)
    {
        if (!unbreakable)
            active = a;
    }

    /**
     * @brief Checks if the brick is unbreakable.
     *
     * @return true if the brick is unbreakable, false otherwise.
     */
    bool IsUnbreakable() const { return unbreakable; }

    /**
     * @brief Sets whether the brick is unbreakable.
     *
     * @param flag true to make the brick unbreakable, false otherwise.
     */
    void SetUnbreakable(bool flag) { unbreakable = flag; }

private:
    bool active;
    bool unbreakable = false;
};

#endif
