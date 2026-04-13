#include "Object3d.h"

Object3D::Object3D() = default;
Object3D::Object3D(const Transform& localTransform, const Transform& worldTransform, const Mesh& mesh)
{
    m_localTransform = localTransform;
    m_worldTransform = worldTransform;
    m_mesh = mesh;
}