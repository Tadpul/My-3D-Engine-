#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include "../math/Vector.h"
#include "OBJLoader.h"

// turns .obj file into a Mesh struct
Mesh OBJLoader::Load(const std::string& path)
{
    std::ifstream file("assets/" + path);
    std::string line;
    std::cout << std::filesystem::current_path() << '\n';
    assert(file && "Error: File failed to load!");

    Mesh mesh;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string type;
        ss >> type;

        if (type == "v")
        {
            float x, y, z;
            ss >> x >> y >> z;
            mesh.vertices.push_back(Vec4{x, y, z, 1});
        }
        else if (type == "f")
        {
            int v0, v1, v2;
            ss >> v0 >> v1 >> v2;
            mesh.faces.push_back(Face{v0 - 1, v1 - 1, v2 - 1});
        }
    }
    return mesh;
}
