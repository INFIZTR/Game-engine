/**
 * @file Main.cpp
 * @brief The entry point for the Brick-Breaker game application.
 *
 * This file contains the main() function which initializes the application,
 * runs the main game loop, and handles application shutdown.
 */

#include "Application.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// C:\MinGW\bin\g++.exe src/main.cpp src/Application.cpp src/Scene.cpp src/Drop.cpp src/TextureComponent.cpp src/ResourceManager.cpp src/GameEntity.cpp src/Paddle.cpp src/Brick.cpp src/Ball.cpp src/InputComponent.cpp src/TransformComponent.cpp src/Collision2DComponent.cpp -I"C:\MinGW\include" -L"C:\MinGW\lib" -o bin/Brick-Breaker.exe -lmingw32 -lSDL2main -lSDL2

/**
 * @brief Program entry point.
 *
 * Initializes SDL, creates an Application instance, and starts the main loop.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return int Exit status code.
 */
int main(int argc, char *argv[])
{
    srand(time(0));

    Application app;
    if (!app.init())
    {
        std::cerr << "Application initialization failed!" << std::endl;
        // std::cin.get();
        return 1;
    }

    app.run();
    // std::cin.get();
    return 0;
}