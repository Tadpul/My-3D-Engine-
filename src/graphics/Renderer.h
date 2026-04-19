#pragma once

#include <SDL3/SDL.h>
#include "../math/Matrix.h"
#include "../loaders/OBJLoader.h"
#include "../object3D/Object3d.h"
#include "Line/ClipLine.h"

void meshToNDC(Object3D& object, std::vector<Vec4>& ndcVertices, int width, int height);
Vec2 NDCToScreen(const Vec4& ndc, int width, int height);
void drawObject(Object3D& object, SDL_Renderer* sdl_renderer, Framebuffer& fb, const std::string& type="wireframe", bool backFaceCulling=true);

