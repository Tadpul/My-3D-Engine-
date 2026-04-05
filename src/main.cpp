#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include "Matrix.h"
#include "Vector.h"

int main()
{
    if (!SDL_Init(SDL_INIT_VIDEO)) return SDL_APP_FAILURE;

    SDL_Window* window = SDL_CreateWindow("my window", 2000, 1000, 0);
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
        }

        if (keys[SDL_SCANCODE_P] == true) SDL_Log("letter p was pressed");
    }

    SDL_Quit();
    return 0;
}