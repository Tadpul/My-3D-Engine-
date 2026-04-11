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
            std::vector<int> vertexIndices{};
            std::string token;
            while (ss >> token) { vertexIndices.push_back(std::stoi(token.substr(0, token.find('/'))) - 1); }

            for(size_t i{ 1 }; i + 1 < vertexIndices.size(); i++)
            {
                mesh.faces.push_back({vertexIndices[0], vertexIndices[i], vertexIndices[i + 1]});
            }
        }
    }
    return mesh;
}
