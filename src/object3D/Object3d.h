#pragma once

#include "Transform.h"
#include "../graphics/Mesh.h"

class Object3D
{
private:
    Transform m_localTransform{};
    Transform m_worldTransform{};
    Mesh m_mesh{};

public:
    Object3D();
    Object3D(const Transform& localTransform, const Transform& worldTransform, const Mesh& mesh);
};