#include <SDL3/SDL.h>
#include <iostream>
#include <string>
#include <cassert>
#include "Matrix.h"
#include "Vector.h"

struct SDLApplication
{
    SDL_Window* m_window{};
    SDL_Renderer* m_renderer{};
    bool running{};

    float r, g, b;
    SDLApplication(const char* windowName, const float& width, const float& length) 
    {
        if (!SDL_Init(SDL_INIT_VIDEO)) std::cout << "Error: " << SDL_GetError() << std::endl;

        // initialise member variables and test if they initialise propperly
        m_window = SDL_CreateWindow(windowName, width, length, 0);
        m_renderer = SDL_CreateRenderer(m_window, nullptr);
        if (!m_renderer) std::cout << "Error: " << SDL_GetError() << std::endl;

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
                r = static_cast<float>(static_cast<int>(event.motion.x) % 225);
                g = static_cast<float>(static_cast<int>(event.motion.y) % 225);
            }
        }
    }

    void Update() {}

    void Render() 
    {
        SDL_SetRenderDrawColor(m_renderer, r, g, 1, 1);
        SDL_RenderClear(m_renderer);
        
        // more drawing operations
        SDL_RenderPresent(m_renderer);
    }

    void MainLoop()
    {
        int fps{};
        Uint64 lastTime{};

        constexpr int targetFps{ 120 };
        Uint64 frameDelay{ static_cast<Uint64>(1000 / targetFps) };

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
                lastTime = SDL_GetTicks();
                std::string title{ "my window FPS: " + std::to_string(fps) };
                SDL_SetWindowTitle(m_window, title.c_str());

                fps = 0;
            }
            // if frame is less than wanted frame delay, delay the app to match target fps
            else if (frameDelay > deltaTime) SDL_Delay(currentTime + frameDelay - SDL_GetTicks());
        }
    }
};

int main()
{
    SDLApplication app("myWindow", 700.0f, 600.0f);
    app.MainLoop();
    return 0;
}