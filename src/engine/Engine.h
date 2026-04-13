#pragma once

#include <SDL3/SDL.h>
#include "../math/Matrix.h"
#include "../graphics/Renderer.h"
#include "../object3D/Object3d.h"

class SDLApplication
{
private:
    SDL_Window* m_window{};
    SDL_Renderer* m_renderer{};

    bool running{};
    int m_width{}, m_height{};

    std::vector<Object3D> m_sceneObjects{};
    size_t m_selectedObject{};

public:
    SDLApplication(const char* windowName, const int width, const int height, const int flags);
    ~SDLApplication();
    void Input();
    void Update();
    void Render();
    void MainLoop();
};