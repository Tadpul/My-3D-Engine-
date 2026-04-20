#include <cstdint>
#include "ClipLine.h"
#include "DrawLine.h"

int outcode(int x, int y, int xmin, int ymin, int xmax, int ymax)
{
    int c = INSIDE;
    if (x < xmin) c |= LEFT;
    else if (x > xmax) c |= RIGHT;
    if (y < ymin) c |= BOTTOM;
    else if (y > ymax) c |= TOP;
    return c;
}

bool clipLine(int& x0, int& y0, int& x1, int& y1, int xmin, int ymin, int xmax, int ymax)
{
    int oc0{ outcode(x0, y0, xmin, ymin, xmax, ymax) };
    int oc1{ outcode(x1, y1, xmin, ymin, xmax, ymax) };

    while (true)
    {
        if (oc0 & oc1) return false; // instantly reject if both point are outside the screen
        if (!(oc0 | oc1 )) return true; // instantly accept if both coordinates are inside the screen

        int oc{ oc0 ? oc0 : oc1 }; // pick one that is outside
        //finds intercepts to attempt to recast the outside point inside the accepted square
        int x, y;
        if (oc & LEFT) { x = xmin; y = y0 + (y1-y0) * (xmin-x0) / (x1-x0); } 
        else if (oc & RIGHT) { x = xmax; y = y0 + (y1-y0) * (xmax-x0) / (x1-x0); }
        else if (oc & TOP) { y = ymax; x = x0 + (x1-x0) * (ymax-y0) / (y1-y0); }
        else { y = ymin; x = x0 + (x1-x0) * (ymin-y0) / (y1-y0); } // BOTTOM

        if (oc == oc0) { x0 = x, y0 = y; oc0 = outcode(x0, y0, xmin, ymin, xmax, ymax); }
        else { x1 = x, y1 = y; oc1 = outcode(x1, y1, xmin, ymin, xmax, ymax); }
    }
}

void drawClippedLine(Framebuffer& fb, int x0, int y0, int x1, int y1, uint32_t colour)
{
    if (clipLine(x0, y0, x1, y1, 0, 0, fb.width - 1, fb.height - 1)) drawLine(fb, x0, y0, x1, y1, colour);
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
    
    drawClippedLine(fb, 100, 7, 1, 1, 0xFF000000);
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