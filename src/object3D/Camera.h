#pragma once

#include "../math/Vector.h"

struct Camera
{
    Vec3 position{};
    float yaw{}; // rotation around y axis (left/right)
    float pitch{}; // rotation around x axis (up/down)
    float radians{ std::acos(-1) / 180 };

    Vec3 forward() const 
    { 
        float cy = std::cos(yaw);
        float sy = std::sin(yaw);
        float cp = std::cos(pitch);
        float sp = std::sin(pitch);

        return { -sy, sp, -cy};
    }

    Vec3 right() const
    {
        Vec3 worldUp{ 0.0f, 1.0f, 0.0f };

        // Cross product: forward × up
        return Vec3::crossProduct(forward(), worldUp);
    }
};