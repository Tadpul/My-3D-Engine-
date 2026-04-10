#pragma once

#include "../graphics/Mesh.h"
#include <string>

class OBJLoader
{
public:
    static Mesh Load(const std::string& path);
};