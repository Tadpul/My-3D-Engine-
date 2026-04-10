#include <SDL3/SDL.h>
#include <iostream>
#include <string>
#include <cassert>
#include <filesystem>
#include "Matrix.h"
#include "Vector.h"

struct SDLApplication
{
    SDL_Window* m_window{};
    SDL_Surface* m_surface{};
    SDL_Surface* m_windowSurface{};
    bool running{};

    SDLApplication(const char* windowName, const float& width, const float& length) 
    {
        if (!SDL_Init(SDL_INIT_VIDEO)) std::cout << "Error: " << SDL_GetError() << std::endl;

        m_window = SDL_CreateWindow(windowName, width, length, 0);
        m_surface = SDL_LoadBMP("assets/FishInTank.bmp");
        if (!m_surface) std::cout << "Error: " << SDL_GetError() << std::endl;
        m_windowSurface = SDL_GetWindowSurface(m_window);

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
            else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
            {
                SDL_Log("%d", event.button.button);
            }
            else if (event.type == SDL_EVENT_KEY_DOWN)
            {
                SDL_Log("buttoncode pressed: %d", event.key.key);
            }
        }
    }

    void Update() {}

    void Render() 
    {
        SDL_BlitSurface(m_surface, nullptr, m_windowSurface, nullptr);
        SDL_UpdateWindowSurface(m_window);
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
    std::cout << "Working dir: " << std::filesystem::current_path() << std::endl;
    SDLApplication app("myWindow", 700.0f, 600.0f);
    app.MainLoop();
    return 0;
}