#pragma once

#include "../buffers/Framebuffer.h"

static inline void plot(Framebuffer& fb, int x, int y, uint32_t colour);
void drawLine(Framebuffer& fb, int x0, int y0, int x1, int y1, uint32_t colour);
