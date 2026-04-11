#pragma once

#include <SDL3/SDL.h>
#include "../math/Matrix.h"
#include "../loaders/OBJLoader.h"

class Renderer
{
public:
    static Vec2 NDCToScreen(const Vec4& ndc, int width, int height);
    static void DrawMesh(Mesh& mesh, const Mat4& transform, SDL_Renderer* sdl_renderer, int width, int height);
};