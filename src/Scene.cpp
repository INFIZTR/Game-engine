#include "Scene.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <SDL2/SDL.h>
#include "InputComponent.h"
#include <cstdlib>
#include <cmath>

/**
 * @brief Constructs a new Scene object.
 *
 * Initializes the scene state.
 */
Scene::Scene() : mRenderer(nullptr), mSceneIsActive(true)
{
}

/**
 * @brief Loads scene data from a file.
 *
 * Reads each line of the scene file to create and initialize game entities.
 * Supported entity types include:
 *  - PADDLE: Creates the player paddle. (Format: PADDLE x y)
 *  - BALL: Creates a ball. (Format: BALL x y vX vY)
 *  - BRICK: Creates a breakable brick and scales it up by 1.5 times. (Format: BRICK x y)
 *  - UNBRICK: Creates an unbreakable brick (using a different texture), scales it up, and marks it as unbreakable.
 *
 * @param sceneFile The path to the scene file.
 * @param renderer The SDL_Renderer used for creating textures and rendering.
 */
void Scene::LoadFromFile(const std::string &sceneFile, SDL_Renderer *renderer)
{

    mRenderer = renderer;

    mPlayerPaddle.reset();
    mBalls.clear();
    mBricks.clear();
    mDrops.clear();

    std::ifstream infile(sceneFile);
    if (!infile.is_open())
    {
        std::cerr << "Can't open the file: " << sceneFile << std::endl;
        return;
    }

    std::cout << "Loading scene from file: " << sceneFile << std::endl;

    std::string line;
    while (std::getline(infile, line))
    {
        if (line.empty() || line[0] == '#')
            continue;

        std::istringstream iss(line);
        std::string entityType;
        iss >> entityType;
        if (entityType == "PADDLE")
        {
            float x, y;
            if (!(iss >> x >> y))
            {
                std::cerr << "Error reading PADDLE data: " << line << std::endl;
                continue;
            }
            mPlayerPaddle = std::make_shared<Paddle>(renderer, "../Assets/paddle.bmp", 500.0f);
            mPlayerPaddle->initComponents(renderer, "../Assets/paddle.bmp");

            std::shared_ptr<InputComponent> inputComp = std::make_shared<InputComponent>();
            inputComp->mSpeed = 300.0f;
            mPlayerPaddle->AddComponent<InputComponent>(inputComp);

            auto paddleTrans = mPlayerPaddle->GetTransform();

            if (paddleTrans)
                paddleTrans->move(x, y);
        }
        else if (entityType == "BALL")
        {
            float x, y, vX, vY;
            if (!(iss >> x >> y >> vX >> vY))
            {
                std::cerr << "Error reading BALL data: " << line << std::endl;
                continue;
            }
            std::shared_ptr<Ball> ball = std::make_shared<Ball>(renderer, "../Assets/ball.bmp", 250.0f);
            ball->initComponents(renderer, "../Assets/ball.bmp");
            auto ballTrans = ball->GetTransform();
            if (ballTrans)
                ballTrans->move(x, y);
            ball->SetVelocity(vX, vY);
            mBalls.push_back(ball);
        }
        else if (entityType == "BRICK")
        {
            float x, y;
            if (!(iss >> x >> y))
            {
                std::cerr << "Error reading BRICK data: " << line << std::endl;
                continue;
            }
            std::shared_ptr<Brick> brick = std::make_shared<Brick>(renderer, "../Assets/brick.bmp");
            brick->initComponents(renderer, "../Assets/brick.bmp");
            auto brickTrans = brick->GetTransform();
            if (brickTrans)
            {
                brickTrans->move(x, y);

                float currentW = brickTrans->getW();
                float currentH = brickTrans->getH();

                brickTrans->setW(currentW * 1.5f);
                brickTrans->setH(currentH * 1.5f);
            }
            mBricks.push_back(brick);
        }
        else if (entityType == "UNBRICK")
        {
            float x, y;
            if (!(iss >> x >> y))
            {
                std::cerr << "Error reading UNBRICK data: " << line << std::endl;
                continue;
            }
            std::shared_ptr<Brick> brick = std::make_shared<Brick>(renderer, "../Assets/unbrick.bmp");
            brick->initComponents(renderer, "../Assets/unbrick.bmp");
            brick->SetUnbreakable(true);
            auto brickTrans = brick->GetTransform();
            if (brickTrans)
            {
                brickTrans->move(x, y);

                float currentW = brickTrans->getW();
                float currentH = brickTrans->getH();

                brickTrans->setW(currentW * 1.5f);
                brickTrans->setH(currentH * 1.5f);
            }
            mBricks.push_back(brick);
        }
        else
        {
            std::cerr << "Unknown entity type: " << entityType << std::endl;
        }
    }
    infile.close();

    std::cout << "Loaded scene: Paddle: " << (mPlayerPaddle ? "yes" : "no")
              << ", Balls count: " << mBalls.size()
              << ", Bricks count: " << mBricks.size() << std::endl;
}

/**
 * @brief Processes input for the scene.
 *
 * Delegates input processing to the player paddle.
 *
 * @param deltaTime The time elapsed since the last frame in seconds.
 */
void Scene::Input(float deltaTime)
{
    if (mPlayerPaddle)
        mPlayerPaddle->Input(deltaTime);
}

/**
 * @brief Updates the scene state.
 *
 * This method updates the player paddle, drops, and balls; processes collisions between drops and the paddle,
 * bricks and balls, and between balls and the paddle; and removes balls that exit the bottom of the screen.
 * If no ball remains, the game is over and the program will exit.
 *
 * @param deltaTime The time elapsed since the last frame in seconds.
 */
void Scene::Update(float deltaTime)
{

    if (mPlayerPaddle)
        mPlayerPaddle->Update(deltaTime);

    for (auto &drop : mDrops)
    {
        drop->Update(deltaTime);
    }

    if (mPlayerPaddle)
    {
        auto paddleColl = mPlayerPaddle->GetComponent<Collision2DComponent>(ComponentType::Collision2DComponent);
        if (paddleColl)
        {
            SDL_FRect paddleRect = paddleColl->getRectangle();
            for (auto it = mDrops.begin(); it != mDrops.end();)
            {
                auto dropTrans = (*it)->GetTransform();
                if (dropTrans)
                {
                    SDL_FRect dropRect = dropTrans->getRectangle();
                    if (SDL_HasIntersectionF(&paddleRect, &dropRect))
                    {
                        size_t currentBallCount = mBalls.size();
                        for (size_t i = 0; i < currentBallCount; ++i)
                        {
                            std::shared_ptr<Ball> newBall = std::make_shared<Ball>(mRenderer, "../Assets/ball.bmp", 250.0f);
                            newBall->initComponents(mRenderer, "../Assets/ball.bmp");
                            auto origBallTrans = mBalls[i]->GetTransform();
                            if (origBallTrans)
                            {
                                SDL_FRect origRect = origBallTrans->getRectangle();
                                newBall->GetTransform()->move(origRect.x + 20, origRect.y);
                            }

                            newBall->SetVelocity(100.0, 100.0);
                            mBalls.push_back(newBall);
                        }
                        it = mDrops.erase(it);
                        continue;
                    }
                }
                ++it;
            }
        }
    }

    for (auto &ball : mBalls)
    {
        ball->Update(deltaTime);
    }

    for (auto &ball : mBalls)
    {
        auto ballTrans = ball->GetTransform();
        if (!ballTrans)
            continue;
        SDL_FRect ballRect = ballTrans->getRectangle();

        for (auto &brick : mBricks)
        {
            if (!brick->IsActive())
                continue;
            auto brickTrans = brick->GetTransform();
            if (!brickTrans)
                continue;
            SDL_FRect brickRect = brickTrans->getRectangle();
            if (SDL_HasIntersectionF(&ballRect, &brickRect))
            {
                if (!brick->IsUnbreakable())
                {
                    brick->SetActive(false);
                    // 30%
                    if ((rand() % 100) < 30)
                    {

                        std::shared_ptr<Drop> drop = std::make_shared<Drop>(mRenderer, "../Assets/drop.bmp", 200.0f);
                        drop->initComponents(mRenderer, "../Assets/drop.bmp");

                        if (brickTrans)
                            drop->GetTransform()->move(brickTrans->getX(), brickTrans->getY());
                        mDrops.push_back(drop);
                    }
                }

                float ballRight = ballRect.x + ballRect.w;
                float brickRight = brickRect.x + brickRect.w;
                float ballBottom = ballRect.y + ballRect.h;
                float brickBottom = brickRect.y + brickRect.h;

                float overlapX = std::min(ballRight, brickRight) - std::max(ballRect.x, brickRect.x);
                float overlapY = std::min(ballBottom, brickBottom) - std::max(ballRect.y, brickRect.y);

                if (overlapX < overlapY)
                {
                    if (ballRect.x < brickRect.x)
                    {
                        ball->GetTransform()->move(brickRect.x - ballRect.w - 1, ballRect.y);
                    }
                    else
                    {
                        ball->GetTransform()->move(brickRect.x + brickRect.w + 1, ballRect.y);
                    }
                    ball->ReverseVelX();
                }
                else
                {
                    if (ballRect.y < brickRect.y)
                    {
                        ball->GetTransform()->move(ballRect.x, brickRect.y - ballRect.h - 1);
                    }
                    else
                    {
                        ball->GetTransform()->move(ballRect.x, brickRect.y + brickRect.h + 1);
                    }
                    ball->ReverseVelY();
                }
                break;
            }
        }
    }

    for (auto &ball : mBalls)
    {
        ball->Update(deltaTime);
    }

    if (mPlayerPaddle)
    {
        auto paddleColl = mPlayerPaddle->GetComponent<Collision2DComponent>(ComponentType::Collision2DComponent);
        if (paddleColl)
        {
            SDL_FRect paddleRect = paddleColl->getRectangle();
            for (auto &ball : mBalls)
            {
                auto ballTrans = ball->GetTransform();
                if (!ballTrans)
                    continue;
                SDL_FRect ballRect = ballTrans->getRectangle();
                if (SDL_HasIntersectionF(&ballRect, &paddleRect))
                {
                    float newY = paddleRect.y - ballRect.h - 1;
                    ball->GetTransform()->move(ballRect.x, newY);
                    ball->ReverseVelY();

                    float paddleVel = mPlayerPaddle->GetInstantaneousVelocity();
                    int sign = 0;
                    if (fabs(paddleVel) < 0.01f)
                    {
                        sign = (rand() % 2 == 0) ? 1 : -1;
                    }
                    else
                    {
                        sign = (paddleVel > 0) ? 1 : -1;
                    }
                    // 10 degree
                    float offsetDeg = 10.0f;
                    float offsetRad = offsetDeg * (M_PI / 180.0f);

                    float vx = ball->GetVelX();
                    float vy = ball->GetVelY();
                    float speed = sqrt(vx * vx + vy * vy);
                    float currentAngle = atan2(vy, vx);

                    float newAngle = currentAngle + sign * offsetRad;

                    ball->SetVelocity(speed * cos(newAngle), speed * sin(newAngle));
                }
            }
        }
    }

    for (auto it = mBalls.begin(); it != mBalls.end();)
    {
        auto ballTrans = (*it)->GetTransform();
        if (ballTrans && ballTrans->getY() > 1000)
        {
            it = mBalls.erase(it);
        }
        else
        {
            ++it;
        }
    }

    if (mBalls.empty())
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "GAME OVER", "GAME OVER! You Failed!", nullptr);
        SDL_Quit();
        exit(0);
    }

    bool allCleared = true;
    for (auto &brick : mBricks)
    {
        if (brick->IsActive() && !brick->IsUnbreakable())
        {
            allCleared = false;
            break;
        }
    }
    if (allCleared)
    {
        mBalls.clear();
        SetSceneStatus(false);
    }
}

/**
 * @brief Renders the scene.
 *
 * Renders the paddle, balls, bricks, and drops.
 *
 * @param renderer The SDL_Renderer used for drawing.
 */
void Scene::Render(SDL_Renderer *renderer)
{
    if (mPlayerPaddle)
        mPlayerPaddle->Render(renderer);
    for (auto &ball : mBalls)
    {
        ball->Render(renderer);
    }
    for (auto &brick : mBricks)
    {
        brick->Render(renderer);
    }
    for (auto &drop : mDrops)
    {
        drop->Render(renderer);
    }
}

/**
 * @brief Shuts down the scene.
 *
 * This method can be used to release resources associated with the scene.
 */
void Scene::SceneShutDown()
{
}

/**
 * @brief Sets the scene's active status.
 *
 * @param active true to mark the scene as active, false otherwise.
 */
void Scene::SetSceneStatus(bool active)
{
    mSceneIsActive = active;
}

/**
 * @brief Gets the scene's active status.
 *
 * @return true if the scene is active; false otherwise.
 */
bool Scene::GetSceneStatus() const
{
    return mSceneIsActive;
}
