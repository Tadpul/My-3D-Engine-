#pragma once

#include "../buffers/Framebuffer.h"
#include "../../math/Vector.h"

void static inline plot(Framebuffer& fb, int x, int y, uint32_t colour);
float static inline edgeFunction(const Vec2& a, const Vec2& b, float x, float y);
bool static inline isTopLeft(const Vec2& a, const Vec2& b);
void boundingBoxFill(Framebuffer& fb, Vec2& v0, Vec2& v1, Vec2& v2, uint32_t colour);