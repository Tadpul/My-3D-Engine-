#pragma once

#include "../math/Vector.h"

struct Camera
{
    Vec3 position{};
    float yaw{}; // rotation around y axis
    float pitch{}; // rotation around x axis

    Vec3 forward()
    { return Vec3{ std::sin(yaw), 0, -std::cos(yaw) }; };

    Vec3 right()
    { return Vec3{ std::cos(yaw), 0, std::sin(yaw) }; };
};

