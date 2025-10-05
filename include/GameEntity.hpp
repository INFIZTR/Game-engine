#pragma once
#include "TextureComponent.hpp"
#include <map>

class GameEntity
{
public:
    /**
     * @brief Handles input for the game entity.
     *
     * @param deltaTime The time elapsed since the last frame, used for frame-independent input handling.
     */
    GameEntity();

    virtual ~GameEntity();

    virtual void Input(float deltaTime);
    virtual void Update(float deltaTime);
    virtual void Render(SDL_Renderer *renderer);

    /**
     * @brief Adds a component to the entity.
     *
     * This function stores a shared pointer to a component in the entity's component map.
     * The component is indexed using its type identifier.
     *
     * @tparam T The type of the component being added.
     * @param c A shared pointer to the component to be added.
     */
    template <typename T>
    void AddComponent(std::shared_ptr<T> c)
    {
        mComponents[c->GetType()] = c;
    }

    /**
     * @brief Retrieves a component of a specified type from the entity.
     *
     * This function looks up the component based on its type and attempts to cast it to
     * the specified template type. If the component is found and can be cast, it returns
     * a shared pointer to it; otherwise, it returns nullptr.
     *
     * @tparam T The expected type of the component.
     * @param type The type identifier of the component to retrieve.
     * @return std::shared_ptr<T> A shared pointer to the requested component, or nullptr if not found.
     */
    template <typename T>
    std::shared_ptr<T> GetComponent(ComponentType type)
    {
        auto found = mComponents.find(type);
        if (found != mComponents.end())
        {
            // Return shared pointer.
            return dynamic_pointer_cast<T>(found->second);
        }

        return nullptr;
    }

    /**
     * @brief Compares the parameter rectangle with the calling GameEntities rectangle to see if there is any overlap.alignas
     *
     * @param otherRect The other rectangle to compare against.
     */
    bool TestCollision(std::shared_ptr<GameEntity> enemy);

    /**
     * @brief Sets whether the entity should be rendered or not.
     *
     * @param renderable A boolean flag indicating if the entity should be drawn.
     */
    void SetRenderable(bool renderable);

    /**
     * @brief Checks if the entity is set to be rendered.
     *
     * @return true If the entity should be rendered.
     * @return false If the entity should not be rendered.
     */
    bool GetRenderable();

protected:
    std::map<ComponentType, std::shared_ptr<Component>> mComponents;
    bool mRenderable{true};
};