#pragma once

#include "../object3D/Mesh.h"
#include <string>

class OBJLoader
{
public:
    static Mesh Load(const std::string& path);
};