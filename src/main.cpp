#include <SDL3/SDL.h>
#include <iostream>
#include <string>
#include "Matrix.h"
#include "Vector.h"

struct SDLApplication
{
    SDL_Window* m_window{};
    bool running{};

    SDLApplication(const char* windowName, const float& width, const float& length) 
    {
        m_window = SDL_CreateWindow(windowName, width, length, 0);
        running = true;
    }

    ~SDLApplication()
    {
        SDL_Quit();
    }

    void Input() 
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT) running = false;
            else if (event.type == SDL_EVENT_MOUSE_MOTION)
            {
                SDL_Log("%d", event.motion.timestamp);
            }
        }
    }

    void Update() {}

    void Render() {}

    void MainLoop()
    {
        int fps{};
        Uint64 lastTime{};

        int targetFps{ 60 };
        Uint64 frameDelay{ 1000 / targetFps };

        while (running)
        {
            // start timer at start of frame and call update function
            Uint64 currentTime{ SDL_GetTicks() };
            Input();
            Update();
            Render();

            // record time taken for update to occur in delta time variable, incrament fps
            Uint64 deltaTime{ SDL_GetTicks() - currentTime };

            // calculate fps
            fps++;
            if (SDL_GetTicks() > 1000 + lastTime) 
            {
                std::string title{ "my window FPS: " + std::to_string(fps) };
                SDL_SetWindowTitle(m_window, title.c_str());

                fps = 0;
                lastTime = SDL_GetTicks();
            }
            else if (frameDelay > deltaTime) SDL_Delay(currentTime + 16.67 - SDL_GetTicks());
        }
    }
};

int main()
{
    SDLApplication app("myWindow", 700.0f, 600.0f);
    app.MainLoop();
    return 0;
}