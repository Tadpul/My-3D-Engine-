#include <algorithm>
#include <cmath>
#include "BoundingBoxTriangle.h"

void static inline plot(Framebuffer& fb, int x, int y, uint32_t colour) 
{
    fb.pixels[y * fb.width + x] = colour;
}

// edge function returns a positive value (if the point is on the right of the edge) or negative (if the point is on the left of the edge)
float static inline edgeFunction(const Vec3& a, const Vec3& b, float x, float y)
{
    return (x - a.x()) * (b.y() - a.y()) - (y - a.y()) * (b.x() - a.x());
}

// function returns true if the edge of the triangle is either a top side or a left side
bool static inline isTopLeft(const Vec3& a, const Vec3& b)
{
    float dx = b.x() - a.x();
    float dy = b.y() - a.y();
    return (dy < 0) || (dy == 0 && dx > 0);
}

void boundingBoxFill(Framebuffer& fb, Vec3& v0, Vec3& v1, Vec3& v2, uint32_t colour)
{
    int xMax{ (int)std::ceil(std::max({v0.x(), v1.x(), v2.x()})) };
    int xMin{ (int)std::floor(std::min({v0.x(), v1.x(), v2.x()})) };
    int yMax{ (int)std::ceil(std::max({v0.y(), v1.y(), v2.y()})) };
    int yMin{ (int)std::floor(std::min({v0.y(), v1.y(), v2.y()})) };

    xMax = std::clamp(xMax, 0, fb.width - 1);
    xMin = std::clamp(xMin, 0, fb.width - 1);
    yMax = std::clamp(yMax, 0, fb.height - 1);
    yMin = std::clamp(yMin, 0, fb.height - 1);

    // edge step increments
    const float dx01{ v1.y() - v0.y() };
    const float dx12{ v2.y() - v1.y() };
    const float dx20{ v0.y() - v2.y() };

    const float dy01{ -(v1.x() - v0.x()) };
    const float dy12{ -(v2.x() - v1.x()) };
    const float dy20{ -(v0.x() - v2.x()) };

    float startX{ xMin + 0.5f };
    float startY{ yMin + 0.5f };

    float rowE0{ edgeFunction(v0, v1, startX, startY) };
    float rowE1{ edgeFunction(v1, v2, startX, startY) };
    float rowE2{ edgeFunction(v2, v0, startX, startY) };

    // top left rule
    bool isTopLeft01{ isTopLeft(v0, v1) };
    bool isTopLeft12{ isTopLeft(v1, v2) };
    bool isTopLeft20{ isTopLeft(v2, v0) };

    // triangle area (constant)
    float area{ edgeFunction(v0, v1, v2.x(), v2.y()) };
    float invArea{ 1.0f / area };

    // precompute z coefficients
    float z0{ v0.z() };
    float z1{ v1.z() };
    float z2{ v2.z() };

    // z interpolation (row start)
    float rowZ{ (rowE1 * z0 + rowE2 * z1 + rowE0 * z2) * invArea };

    // z increments
    float dzdx{ (dx12 * z0 + dx20 * z1 + dx01 * z2) * invArea };
    float dzdy{ (dy12 * z0 + dy20 * z1 + dy01 * z2) * invArea };

    for (int y = yMin; y <= yMax; y++)
    {
        float E0{ rowE0 };
        float E1{ rowE1 };
        float E2{ rowE2 };

        float z{ rowZ };

        for (int x = xMin; x <= xMax; x++)
        {
            if ((E0 > 0 || (E0 == 0 && isTopLeft01)) &&
                (E1 > 0 || (E1 == 0 && isTopLeft12)) &&
                (E2 > 0 || (E2 == 0 && isTopLeft20)))
            {
                int index = y * fb.width + x;
                if (z <= fb.zBuffer[index])
                {
                    fb.zBuffer[index] = z;
                    fb.pixels[index] = colour;
                }
            }

            E0 += dx01;
            E1 += dx12;
            E2 += dx20;

            z += dzdx;
        }

        rowE0 += dy01;
        rowE1 += dy12;
        rowE2 += dy20;

        rowZ += dzdy;
    }
}