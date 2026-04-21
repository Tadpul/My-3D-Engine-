#pragma once

#include <cstdint>
#include "../buffers/Framebuffer.h"

void static inline drawBottomTriangle(Framebuffer& fb, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t colour);
void static inline drawTopTriangle(Framebuffer& fb, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t colour);
void drawScalineTriangle(Framebuffer& fb, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t colour);