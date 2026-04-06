#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <SDL3/SDL_render.h>
#include "Matrix.h"
#include "Vector.h"

std::array<float, 2> screenToWorldTransform(const float &xScreenSize, const float &yScreenSize, float &xSDL, float &ySDL)
{
    const float displacementFactor{ 1 / std::min(xScreenSize, yScreenSize) };
    const float x = 2 * (xSDL - 0.5*xScreenSize) * displacementFactor;
    const float y = -2 * (ySDL + 0.5*yScreenSize) * displacementFactor + 2;
    return std::array<float, 2>{x, y};
}

int main()
{
    if (!SDL_Init(SDL_INIT_VIDEO)) return SDL_APP_FAILURE;

    constexpr float xScreenSize{ 2000 };
    constexpr float yScreenSize{ 1000 };
    SDL_Window* window = SDL_CreateWindow("my window", xScreenSize, yScreenSize, 0);
    SDL_Renderer* renderer;
    SDL_Event event;    

    const bool* keys = SDL_GetKeyboardState(nullptr);

    // application runs until exit
    bool running{ true };
    while (running)
    {
        // event handling loop
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT) running = false;
            else if (event.type == SDL_EVENT_KEY_DOWN) 
            {
                SDL_Log("a key was pressed: %d", event.key.scancode);
            }
            else if (event.type == SDL_EVENT_MOUSE_MOTION)
            {
                std::array<float, 2> worldCoordinates{ screenToWorldTransform(xScreenSize, yScreenSize, event.motion.x, event.motion.y) };
                SDL_Log("x, y: %f, %f", worldCoordinates[0], worldCoordinates[1]);
            }
        }

        if (keys[SDL_SCANCODE_P] == true) SDL_Log("letter p was pressed");
    }

    SDL_Quit();
    return 0;
}