#pragma once

#include "../buffers/Framebuffer.h"
#include "../../math/Vector.h"

void static inline plot(Framebuffer& fb, int x, int y, uint32_t colour);
float onLeft(Vec2& vB, Vec2& vec, int xP, int yP);
void boundingBoxFill(Framebuffer& fb, Vec2& v0, Vec2& v1, Vec2& v2, uint32_t colour);
