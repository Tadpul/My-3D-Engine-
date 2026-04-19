#include <algorithm>
#include "DrawLine.h"

static inline void plot(Framebuffer& fb, int x, int y, uint32_t colour)
{
    fb.pixels[ y * fb.width + x ] = colour;
}

void drawLine(Framebuffer& fb, int x0, int y0, int x1, int y1, uint32_t colour)
{
    const int dx{ std::abs(x1 - x0) };
    const int dy{ std::abs(y1 - y0) };
    const int sx{ x1 - x0 > 0 ? 1 : -1 };
    const int sy{ y1 - y0 > 0 ? 1 : -1 };

    int err = dx - dy;
    while (true)
    {
        plot(fb, x0, y0, colour);
        if (x0 == x1 && y0 == y1) break;
        const int err2{ err * 2 };

        if (err2 > -dy) { x0 += sx; err -= dy; }
        if (err2 < dx) { y0 += sy; err += dx; }
    }
}

#ifdef debug

#include <iostream>

int main()
{
    Framebuffer fb;
    fb.width = 20;
    fb.height = 20;
    fb.pitch = fb.width * sizeof(uint32_t);
    fb.pixels.resize(fb.width * fb.height);
    
    drawLine(fb, 10, 1, 1, 1, 0xFF000000);
    for (int y = 0; y < fb.height; y++)
    {
        for (int x = 0; x < fb.width; x++)
        {
            if (fb.pixels[y * fb.width + x] == 0)
                std::cout << ". ";
            else
                std::cout << "# ";
        }
        std::cout << '\n';
    }
}

#endif