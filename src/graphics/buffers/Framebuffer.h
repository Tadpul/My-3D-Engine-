#pragma once

#include <cstdint>
#include <vector>

struct Framebuffer
{
    int width;
    int height;
    int pitch;

    std::vector<uint32_t> pixels;
};