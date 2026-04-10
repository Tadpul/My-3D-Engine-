#include <SDL3/SDL.h>
#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>
#include "math/Matrix.h"
#include "math/Vector.h"
#include "graphics/Renderer.h"

struct SDLApplication
{
    SDL_Window* m_window{};
    SDL_Renderer* m_renderer{};
    Mesh m_objCube;
    bool running{};
    int m_width, m_height;

    float mousePositionX, mousePositionY;
    SDLApplication(const char* windowName, const float& width, const float& height) 
    {
        if (!SDL_Init(SDL_INIT_VIDEO)) std::cout << "Error: " << SDL_GetError() << std::endl;

        // initialise member variables and test if they initialise propperly
        m_window = SDL_CreateWindow(windowName, width, height, 0);
        m_renderer = SDL_CreateRenderer(m_window, nullptr);
        if (!m_renderer) std::cout << "Error: " << SDL_GetError() << std::endl;

        // load cube mesh
        m_objCube = OBJLoader::Load("untitled.obj");

        // set background colour
        SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 1);
        SDL_RenderClear(m_renderer);

        running = true;
        m_width = width; m_height = height;
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
                mousePositionX = event.motion.x;
                mousePositionY = event.motion.y;
            }
        }
    }

    void Update() {}

    void Render() 
    {
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
        Mat4 transform{ Mat4::projection(-20, 20, 20, 20, 0.5, 5) * Mat4::scale(std::min(m_width, m_height)) };
        Renderer::DrawMesh(m_objCube, transform, m_renderer);
        
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