#pragma once

#include <SDL3/SDL.h>
#include "../math/Matrix.h"
#include "../graphics/Renderer.h"

class SDLApplication
{
private:
    SDL_Window* m_window{};
    SDL_Renderer* m_renderer{};
    Mesh m_obj;
    bool running{};
    int m_width, m_height;
    Mat4 m_rotation{};

public:
    SDLApplication(const char* windowName, const int width, const int height, const int flags);
    ~SDLApplication();
    void Input();
    void Update();
    void Render();
    void MainLoop();
};