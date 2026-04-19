#pragma once

#include <vector>
#include "../math/Vector.h"

struct Face { int v0{}, v1{}, v2{}; };
struct Mesh
{
    std::vector<Vec4> vertices{};
    std::vector<Face> faces{};
};