#ifndef DROP_H
#define DROP_H

#include "GameEntity.h"

/**
 * @brief The Drop class represents a falling drop object.
 *
 * The Drop object is spawned when a brick is broken (if the drop chance condition is met).
 * It falls vertically downward at a specified speed and can interact with the paddle.
 * This class inherits from GameEntity.
 */
class Drop : public GameEntity
{
public:
    Drop(SDL_Renderer *renderer, const char *texturePath, float speed);
    virtual void Update(float deltaTime) override;
};

#endif
