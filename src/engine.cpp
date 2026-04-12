#include <SDL3/SDL.h>
#include <string>
#include <cassert>
#include "math/Matrix.h"
#include "math/Vector.h"
#include "graphics/Renderer.h"

struct SDLApplication
{
    SDL_Window* m_window{};
    SDL_Renderer* m_renderer{};
    Mesh m_obj;
    bool running{};
    int m_width, m_height;
    float m_angleY, m_angleX;

    float mousePositionX, mousePositionY;
    SDLApplication(const char* windowName, const int width, const int height) 
    {
        if (!SDL_Init(SDL_INIT_VIDEO)) std::cout << "Error: " << SDL_GetError() << std::endl;
        m_width = width; m_height = height;

        // initialise member variables and test if they initialise propperly
        m_window = SDL_CreateWindow(windowName, width, height, 0);
        m_renderer = SDL_CreateRenderer(m_window, nullptr);
        if (!m_renderer) std::cout << "Error: " << SDL_GetError() << std::endl;

        // load cube mesh
        m_obj = OBJLoader::Load("monkey.obj");

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
                m_angleY += event.motion.xrel * (std::acos(0) / 180.0f);
                m_angleX += event.motion.yrel * (std::acos(0) / 180.0f);
            }
        }
    }

    void Update() {}

    void Render() 
    {
        // set background colour
        SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
        SDL_RenderClear(m_renderer);

        // render cube wireframe
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);

        Mat4 rotationY{ Mat4::rotateY(m_angleY) };
        Mat4 rotationX{ Mat4::rotateX(m_angleX) };
        Mat4 translation{ Mat4::translate(0, 0, 5.0f) };
        Mat4 scale{ Mat4::scale(1) };
        Mat4 projection{ Mat4::projection(-0.5f, 0.5f, -0.5f, 0.5f, 1.0f, 100.0f) };
        Mat4 transform = scale * projection * translation * rotationX * rotationY * scale;
        Renderer::DrawMesh(m_obj, transform, m_renderer, m_width, m_height);
        
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