#include <algorithm>
#include <cmath>
#include "BoundingBoxTriangle.h"

void static inline plot(Framebuffer& fb, int x, int y, uint32_t colour) 
{
    fb.pixels[y * fb.width + x] = colour;
}

float onLeft(Vec2& vB, Vec2& vL, int xP, int yP)
{
    return ( (xP - vB.x()) * (vL.y() - vB.y()) - (yP - vB.y()) * (vL.x() - vB.x()) );
}

void boundingBoxFill(Framebuffer& fb, Vec2& v0, Vec2& v1, Vec2& v2, uint32_t colour)
{
    int xMax{ static_cast<int>(std::ceil( std::max({v0.x(), v1.x(), v2.x()}) )) };
    int xMin{ static_cast<int>(std::floor( std::min({v0.x(), v1.x(), v2.x()}) )) };
    int yMax{ static_cast<int>(std::ceil( std::max({v0.y(), v1.y(), v2.y()}) )) };
    int yMin{ static_cast<int>(std::floor( std::min({v0.y(), v1.y(), v2.y()}) )) };

    xMax = std::clamp(xMax, 0, fb.width - 1);
    xMin = std::clamp(xMin, 0, fb.width - 1);
    yMax = std::clamp(yMax, 0, fb.height - 1);
    yMin = std::clamp(yMin, 0, fb.height - 1);

    for (int y{ yMin }; y < yMax; y++)
    {
        for (int x{ xMin }; x < xMax; x++)
        {
            if (onLeft(v2, v0, x, y) >= 0 && onLeft(v0, v1, x, y) >= 0 && onLeft(v1, v2, x, y) >= 0)
            {
                plot(fb, x, y, colour);
            }
        }
    }
}