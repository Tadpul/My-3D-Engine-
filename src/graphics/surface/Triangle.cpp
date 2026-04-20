#include "Triangle.h"

void drawBottomTriangle(Framebuffer& fb, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t colour)
{
    if (x0 < x1) std::swap(x0, x1); // x0 = right, x1 = left

    float mInverseLeft { static_cast<float>(x2 - x1) / (y2 - y1) }; // left x gradient (negative)
    float mInverseRight { static_cast<float>(x2 - x0) / (y2 - y0) }; // right x gradient (positive)

    float left{ static_cast<float>(x1) };
    float right{ static_cast<float>(x0) };

    for (size_t y{ static_cast<size_t>(y0) }; y <= static_cast<size_t>(y2); y++)
    {
        for (size_t x{ static_cast<size_t>(left) }; x <= static_cast<size_t>(right); x++) 
        {
            if (static_cast<int>(x) >= 0 && x < static_cast<size_t>(fb.width) && static_cast<int>(y) >= 0 && y < static_cast<size_t>(fb.height))
            fb.pixels[y * fb.width + x] = colour;
        }
        left += mInverseLeft;
        right += mInverseRight;
    }
}

void drawTopTriangle(Framebuffer& fb, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t colour)
{
    if (x2 < x1) std::swap(x2, x1); // x2 = right, x1 = left

    float mInverseLeft { static_cast<float>(x1 - x0) / (y1 - y0) }; // left x gradient (negative)
    float mInverseRight { static_cast<float>(x2 - x0) / (y2 - y0) }; // right x gradient (positive)

    float left{ static_cast<float>(x0) };
    float right{ static_cast<float>(x0) };

    for (size_t y{ static_cast<size_t>(y0) }; y <= static_cast<size_t>(y1); y++)
    {
        for (size_t x{ static_cast<size_t>(left) }; x <= static_cast<size_t>(right); x++) 
        {
            if (static_cast<int>(x) >= 0 && x < static_cast<size_t>(fb.width) && static_cast<int>(y) >= 0 && y < static_cast<size_t>(fb.height))
            fb.pixels[y * fb.width + x] = colour;
        }
        left += mInverseLeft;
        right += mInverseRight;
    }
}

void drawScalineTriangle(Framebuffer& fb, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t colour)
{
    if (y0 > y1) { std::swap(x0, x1); std::swap(y0, y1); }
    if (y1 > y2) { std::swap(x1, x2); std::swap(y1, y2); }
    if (y0 > y1) { std::swap(x0, x1); std::swap(y0, y1); }

    if (y0 == y2) return;
    else if (y1 == y2) drawTopTriangle(fb, x0, y0, x1, y1, x2, y2, colour);
    else if (y0 == y1) drawBottomTriangle(fb, x0, y0, x1, y1, x2, y2, colour);
    else
    {
        int xmid = ( y1 - y2 ) * (x2 - x0) / (y2 - y0) + x2;
        drawBottomTriangle(fb, xmid, y1, x1, y1, x2, y2, colour);
        drawTopTriangle(fb, x0, y0, x1, y1, xmid, y1, colour);
    }
}

#ifdef debug

include <iostream>

int main()
{
    Framebuffer fb;
    fb.width = 20;
    fb.height = 20;
    fb.pitch = fb.width * sizeof(uint32_t);
    fb.pixels.resize(fb.width * fb.height, 0);

    drawScalineTriangle(fb, 5, 3, 0, 0, 18, 19, 10);
    int y{ 0 };
    int x{ 0 };
    fb.pixels[y * fb.width + x] = 100;
    
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