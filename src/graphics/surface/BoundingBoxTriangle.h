#pragma once

#include "../buffers/Framebuffer.h"
#include "../../math/Vector.h"

void static inline plot(Framebuffer& fb, int x, int y, uint32_t colour);
float static inline edgeFunction(const Vec3& a, const Vec3& b, float x, float y);
bool static inline isTopLeft(const Vec3& a, const Vec3& b);
void boundingBoxFill(Framebuffer& fb, Vec3& v0, Vec3& v1, Vec3& v2, uint32_t colour);