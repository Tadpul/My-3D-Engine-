#include "Engine.h"
#include <string>
#include <cstdint>
#include <algorithm>

SDLApplication::SDLApplication(const char* windowName, const int width, const int height, const int flags=0) 
{
    if (!SDL_Init(SDL_INIT_VIDEO)) std::cout << "Error: " << SDL_GetError() << std::endl;
    m_width = width; m_height = height;

    // initialise member variables and test if they initialise propperly
    m_window = SDL_CreateWindow(windowName, width, height, flags);
    m_renderer = SDL_CreateRenderer(m_window, nullptr);
    if (!m_renderer) std::cout << "Error: " << SDL_GetError() << std::endl;

    // initialise the frame buffer and corresponding texture
    m_scale = std::clamp(m_scale, 1, std::min(m_width, m_height));
    updateFramebuffer();

    // loads objects into view vector and offsets them on screen
    m_sceneObjects.push_back(OBJLoader::Load("cogRobot.obj"));
    m_sceneObjects[0].getLocalTransform().translateObject({0.0f, 0.0f, -4.0f});

    running = true;
}

SDLApplication::~SDLApplication()
{
    SDL_DestroyTexture(m_texture);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
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

            updateFramebuffer();
        }
        else if (event.type == SDL_EVENT_KEY_DOWN)
        {
            size_t index = event.key.key - SDLK_1; 
            if (index < m_sceneObjects.size())
            {
                m_selectedObject = index;
            }
            else if (event.key.key == SDLK_EQUALS && (event.key.mod & SDLK_LSHIFT))
            {
                m_scale = std::clamp(m_scale + 1, 1, std::min(m_width, m_height));
                updateFramebuffer();
            }
            else if (event.key.key == SDLK_MINUS || event.key.key == SDLK_KP_MINUS)
            {
                m_scale = std::clamp(m_scale - 1, 1, std::min(m_width, m_height));
                updateFramebuffer();
            }
            else if (event.key.key == SDLK_O) m_renderingMode = "object";
            else if (event.key.key == SDLK_W) m_renderingMode = "wireframe";
        }
    }
}

void SDLApplication::Update() {}

void SDLApplication::Render() 
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    std::fill(m_fb.pixels.begin(), m_fb.pixels.end(), 0x00000000);

    for (Object3D& object : m_sceneObjects) { drawObject(object, m_renderer, m_fb, m_renderingMode, true); }
    SDL_UpdateTexture(m_texture, nullptr, m_fb.pixels.data(), m_fb.pitch);

    // clear renderer with a background colour and then render the texture 
    SDL_RenderTexture(m_renderer, m_texture, nullptr, nullptr);

    // more drawing operations
    SDL_RenderPresent(m_renderer);
}

void SDLApplication::updateFramebuffer()
{
    m_fb.width = m_width / m_scale;
    m_fb.height = m_height / m_scale;
    m_fb.pitch = m_fb.width * sizeof(uint32_t);
    m_fb.pixels.assign(m_fb.width * m_fb.height, 0x00000000);

    if (m_texture) SDL_DestroyTexture(m_texture);
    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, m_fb.width, m_fb.height);
    SDL_SetTextureScaleMode(m_texture, SDL_SCALEMODE_NEAREST);
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

