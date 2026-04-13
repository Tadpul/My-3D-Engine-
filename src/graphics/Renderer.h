#pragma once

#include <SDL3/SDL.h>
#include "../math/Matrix.h"
#include "../loaders/OBJLoader.h"
#include "../object3D/Object3d.h"

class Renderer
{
private:
    static void meshToNDC(Object3D& object, std::vector<Vec4>& ndcVertices, int width, int height);
    static Vec2 NDCToScreen(const Vec4& ndc, int width, int height);
    static void drawFaces(SDL_Renderer* sdl_renderer, const Face& face, const std::vector<Vec2>& sdlVertices);
    
public:
    static void DrawObject(Object3D& object, SDL_Renderer* sdl_renderer, int width, int height, bool backFaceCulling);
};

