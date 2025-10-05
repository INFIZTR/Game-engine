#include "Application.h"
#include "Scene.h"
#include <iostream>
#include <SDL2/SDL.h>

/**
 * @brief Constructs a new Application object.
 */
Application::Application()
    : mWindow(nullptr),
      mRenderer(nullptr),
      mRun(true),
      mWindowWidth(1600),
      mWindowHeight(1000),
      mCurrentSceneIndex(0)
{
}

/**
 * @brief Destroys the Application object.
 *
 * This destructor cleans up the SDL renderer and window, then quits SDL.
 */
Application::~Application()
{
    if (mRenderer)
        SDL_DestroyRenderer(mRenderer);
    if (mWindow)
        SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

/**
 * @brief Initializes the application.
 *
 * Initializes SDL, creates a window and renderer, and loads the scenes from file.
 *
 * @return true if initialization is successful, false otherwise.
 */
bool Application::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    mWindow = SDL_CreateWindow("Brick-Breaker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               mWindowWidth, mWindowHeight, SDL_WINDOW_SHOWN);
    if (!mWindow)
    {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!mRenderer)
    {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(mWindow);
        SDL_Quit();
        return false;
    }

    // Load scene1 from file
    std::unique_ptr<Scene> scene1 = std::make_unique<Scene>();
    scene1->LoadFromFile("../Scenes/scene1.txt", mRenderer);
    mScenes.push_back(std::move(scene1));
    // Load scene2 from file
    std::unique_ptr<Scene> scene2 = std::make_unique<Scene>();
    scene2->LoadFromFile("../Scenes/scene2.txt", mRenderer);
    mScenes.push_back(std::move(scene2));
    // Load scene3 from file
    std::unique_ptr<Scene> scene3 = std::make_unique<Scene>();
    scene3->LoadFromFile("../Scenes/scene3.txt", mRenderer);
    mScenes.push_back(std::move(scene3));

    mCurrentSceneIndex = 0;

    return true;
}

/**
 * @brief Processes input events and passes them to the current scene.
 *
 * @param deltaTime Time elapsed since last frame, in seconds.
 */
void Application::processInput(float deltaTime)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            mRun = false;
        }
    }

    if (!mScenes.empty())
    {
        mScenes[mCurrentSceneIndex]->Input(deltaTime);
    }
}

/**
 * @brief Updates the current scene.
 *
 * If the current scene is ended, switches to the next scene if available,
 * or exits the application if there are no more scenes.
 *
 * @param deltaTime Time elapsed since last frame, in seconds.
 */
void Application::update(float deltaTime)
{
    if (!mScenes.empty())
    {
        mScenes[mCurrentSceneIndex]->Update(deltaTime);
        if (!mScenes[mCurrentSceneIndex]->GetSceneStatus())
        {
            std::cout << "Current scene index: " << mCurrentSceneIndex
                      << ", status: " << (mScenes[mCurrentSceneIndex]->GetSceneStatus() ? "active" : "ended")
                      << std::endl;
            if (mCurrentSceneIndex + 1 < mScenes.size())
            {
                mCurrentSceneIndex++;
            }
            else
            {
                mRun = false;
            }
        }
    }
}

/**
 * @brief Renders the current scene.
 */
void Application::render()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);

    if (!mScenes.empty())
    {
        mScenes[mCurrentSceneIndex]->Render(mRenderer);
    }

    SDL_RenderPresent(mRenderer);
}

/**
 * @brief Runs the main game loop.
 *
 * The loop processes input, updates the game, and renders the scene at fixed frame rate.
 */
void Application::run()
{
    const int targetFPS = 60;
    const int frameDelay = 1000 / targetFPS;
    Uint32 lastFrameTime = SDL_GetTicks();

    while (mRun)
    {
        Uint32 currentFrameTime = SDL_GetTicks();
        float deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f;
        lastFrameTime = currentFrameTime;

        processInput(deltaTime);
        update(deltaTime);
        render();

        int frameTime = SDL_GetTicks() - currentFrameTime;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}
