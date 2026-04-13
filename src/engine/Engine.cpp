#include "Engine.h"
#include <string>
#include <algorithm>

SDLApplication::SDLApplication(const char* windowName, const int width, const int height, const int flags=0) 
{
    if (!SDL_Init(SDL_INIT_VIDEO)) std::cout << "Error: " << SDL_GetError() << std::endl;
    m_width = width; m_height = height;

    // initialise member variables and test if they initialise propperly
    m_window = SDL_CreateWindow(windowName, width, height, flags);
    m_renderer = SDL_CreateRenderer(m_window, nullptr);
    if (!m_renderer) std::cout << "Error: " << SDL_GetError() << std::endl;

    // load cube mesh
    m_obj = OBJLoader::Load("cube.obj");

    running = true;
    m_rotation = Mat4::identity();
}

SDLApplication::~SDLApplication()
{
    SDL_Quit();
}

void SDLApplication::Input() 
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT) running = false;
        else if (event.type == SDL_EVENT_MOUSE_MOTION)
        {
            float dx = event.motion.xrel * (std::acos(-1) / 180.0f);
            float dy = event.motion.yrel * (std::acos(-1) / 180.0f);

            m_rotation = Mat4::rotateX(dy) * Mat4::rotateY(dx) * m_rotation;
        }
        else if (event.type == SDL_EVENT_WINDOW_RESIZED)
        {
            m_width = event.window.data1;
            m_height = event.window.data2;
        }
    }
}

void SDLApplication::Update() {}

void SDLApplication::Render() 
{
    // set background colour
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);

    // render cube wireframe
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);

    Mat4 scale{ Mat4::scale(1) };
    Mat4 translation{ Mat4::translate(0, 0, -5.0f) };
    Mat4 transform = translation * m_rotation * scale;

    Renderer::DrawMesh(m_obj, transform, m_renderer, m_width, m_height, true);
    
    // more drawing operations
    SDL_RenderPresent(m_renderer);
}

void SDLApplication::MainLoop()
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