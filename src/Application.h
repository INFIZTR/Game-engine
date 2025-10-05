#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include "Scene.h"

/**
 * @brief The Application class encapsulates the entire game application.
 *
 * It manages SDL initialization, window and renderer creation, and the main game loop.
 * It also holds a vector of Scene objects and controls scene switching.
 */
class Application
{
public:
    Application();
    ~Application();

    bool init();
    void run();

private:
    void processInput(float deltaTime);
    void update(float deltaTime);
    void render();

    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    bool mRun;
    int mWindowWidth;
    int mWindowHeight;

    std::vector<std::unique_ptr<Scene>> mScenes;
    size_t mCurrentSceneIndex;
};

#endif
