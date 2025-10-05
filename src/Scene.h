#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include <string>
#include <SDL2/SDL.h>
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "Drop.h"

/**
 * @brief The Scene class encapsulates a game scene.
 *
 * A Scene manages game entities such as the player paddle, balls, bricks, and drops.
 * It provides methods for loading the scene data from a file, processing input,
 * updating all entities, rendering the scene, and determining the scene state.
 */
class Scene
{
public:
    Scene();

    void LoadFromFile(const std::string &sceneFile, SDL_Renderer *renderer);

    void Input(float deltaTime);
    void Update(float deltaTime);
    void Render(SDL_Renderer *renderer);
    void SceneShutDown();
    void SetSceneStatus(bool active);
    bool GetSceneStatus() const;

private:
    std::shared_ptr<Paddle> mPlayerPaddle;
    std::vector<std::shared_ptr<Ball>> mBalls;
    std::vector<std::shared_ptr<Brick>> mBricks;
    std::vector<std::shared_ptr<Drop>> mDrops;

    SDL_Renderer *mRenderer;
    bool mSceneIsActive;
};

#endif
