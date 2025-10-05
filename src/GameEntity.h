#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "TextureComponent.h"
#include "TransformComponent.h"
#include "Collision2DComponent.h"
#include "../include/Component.hpp"
#include "../include/ComponentType.hpp"
#include <map>
#include <memory>
#include <SDL2/SDL.h>

/**
 * @brief The GameEntity class serves as the base class for all game objects.
 *
 * It implements a component-based system where components such as texture,
 * transform and collision are stored in a map. Derived classes can add or override
 * functionality by adding or replacing components.
 */
class GameEntity : public std::enable_shared_from_this<GameEntity>
{
public:
    std::map<ComponentType, std::shared_ptr<Component>> mComponents;

    GameEntity(SDL_Renderer *renderer, const char *texturePath, float speed);
    virtual ~GameEntity() = default;

    /**
     * @brief Sets the horizontal movement direction for the entity.
     *
     * @param dir Direction indicator (-1 for left, 1 for right, etc.)
     */
    void SetDirection(int dir) { xPositiveDirection = dir; }

    virtual void Input(float deltaTime) {}
    virtual void Update(float deltaTime);
    virtual void Render(SDL_Renderer *renderer);

    float getX() const;
    float getY() const;

    bool TestCollision(std::shared_ptr<GameEntity> other);

    /**
     * @brief Returns a shared pointer to this GameEntity.
     *
     * Useful for adding components to this entity.
     *
     * @return std::shared_ptr<GameEntity> The shared pointer to this object.
     */
    std::shared_ptr<GameEntity> GetThisPtr()
    {
        return shared_from_this();
    }

    /**
     * @brief Adds a component to the entity.
     *
     * The component's ownership is associated with this entity.
     *
     * @tparam T The type of the component.
     * @param comp A shared pointer to the component.
     */
    template <typename T>
    void AddComponent(std::shared_ptr<T> comp)
    {
        comp->SetGameEntity(GetThisPtr());
        mComponents[comp->GetType()] = comp;
    }

    /**
     * @brief Retrieves a component by its type.
     *
     * @tparam T The expected type of the component.
     * @param type The component type identifier.
     * @return std::shared_ptr<T> The shared pointer to the requested component, or nullptr if not found.
     */
    template <typename T>
    std::shared_ptr<T> GetComponent(ComponentType type)
    {
        auto it = mComponents.find(type);
        if (it != mComponents.end())
        {
            return std::dynamic_pointer_cast<T>(it->second);
        }
        return nullptr;
    }

    /**
     * @brief Initializes basic components for the game entity.
     *
     * Creates and adds a TextureComponent, a TransformComponent, and a Collision2DComponent
     * using the given texture path. The initial transform and collision dimensions are based on the texture size.
     *
     * @param renderer The SDL_Renderer used for creating components.
     * @param texturePath The path to the texture file.
     */
    void initComponents(SDL_Renderer *renderer, const char *texturePath)
    {
        std::shared_ptr<TextureComponent> texComp = std::make_shared<TextureComponent>(renderer, texturePath);
        AddComponent<TextureComponent>(texComp);

        std::shared_ptr<TransformComponent> transComp = std::make_shared<TransformComponent>(0, 0, texComp->getRectangle().w, texComp->getRectangle().h);
        AddComponent<TransformComponent>(transComp);

        std::shared_ptr<Collision2DComponent> collComp = std::make_shared<Collision2DComponent>(0, 0, texComp->getRectangle().w, texComp->getRectangle().h);
        AddComponent<Collision2DComponent>(collComp);
    }

    /**
     * @brief Returns the entity's TransformComponent.
     *
     * @return std::shared_ptr<TransformComponent> The transform component.
     */
    std::shared_ptr<TransformComponent> GetTransform()
    {
        return GetComponent<TransformComponent>(ComponentType::TransformComponent);
    }

    /**
     * @brief Returns the entity's Collision2DComponent.
     *
     * @return std::shared_ptr<Collision2DComponent> The collision component.
     */
    std::shared_ptr<Collision2DComponent> GetCollision2D()
    {
        return GetComponent<Collision2DComponent>(ComponentType::Collision2DComponent);
    }

protected:
    float mSpeed;
    int xPositiveDirection;
    bool renderable = true;
};

#endif
