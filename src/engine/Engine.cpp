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
#
    m_sceneObjects.push_back(OBJLoader::Load("cube.obj"));
    m_sceneObjects.push_back(OBJLoader::Load("monkey.obj"));
    m_sceneObjects[0].getLocalTransform().translateObject({0.0f, 0.0f, -5.0f});
    m_sceneObjects[1].getLocalTransform().translateObject({4.0f, 0.0f, -10.0f});

    running = true;
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

            float angleX = m_sceneObjects[m_selectedObject].getLocalTransform().getTransform()[1][0] + dy;
            float angleY = m_sceneObjects[m_selectedObject].getLocalTransform().getTransform()[1][1] + dx;
            m_sceneObjects[m_selectedObject].getLocalTransform().rotateObject({angleX, angleY, 0});
        }
        else if (event.type == SDL_EVENT_WINDOW_RESIZED)
        {
            m_width = event.window.data1;
            m_height = event.window.data2;
        }
        else if (event.type == SDL_EVENT_KEY_DOWN)
        {
            size_t index = event.key.key - SDLK_1; 
            if (index < m_sceneObjects.size())
            {
                m_selectedObject = index;
                std::cout << "Selected object: " << m_selectedObject << '\n';
            }
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

    for (Object3D& object : m_sceneObjects) { Renderer::DrawObject(object, m_renderer, m_width, m_height, true); }

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