#pragma once

#include "../buffers/Framebuffer.h"

enum OutCode : int 
{
    INSIDE = 0, LEFT = 1, RIGHT = 2, BOTTOM = 4, TOP = 8
};

int outcode(int x, int y, int xmin, int ymin, int xmax, int ymax);
bool clipLine(int& x0, int& y0, int& x1, int& y1, int xmin, int ymin, int xmax, int ymax);
void drawClippedLine(Framebuffer& fb, int x0, int y0, int x1, int y1, uint32_t colour);