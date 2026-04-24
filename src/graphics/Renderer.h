#pragma once

#include <SDL3/SDL.h>
#include "../math/Matrix.h"
#include "../loaders/OBJLoader.h"
#include "../object3D/Object3d.h"
#include "../object3D/Camera.h"
#include "Line/ClipLine.h"

void meshToNDC(Object3D& object, std::vector<Vec4>& ndcVertices, const Camera& camera, int width, int height);
Vec3 NDCToScreen(const Vec4& ndc, int width, int height);
void drawObject(Object3D& object, SDL_Renderer* sdl_renderer, Framebuffer& fb, const Camera& camera, const std::string& type, bool backFaceCulling);

