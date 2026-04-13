#include "Object3d.h"

Object3D::Object3D() = default;
Object3D::Object3D(const Mesh& mesh) { m_mesh = mesh; }
Object3D::Object3D(const Transform& localTransform, const Transform& worldTransform, const Mesh& mesh)
{
    m_localTransform = localTransform;
    m_worldTransform = worldTransform;
    m_mesh = mesh;
}

Transform& Object3D::getLocalTransform() { return m_localTransform; }
Transform& Object3D::getWorldTransform() { return m_worldTransform; }
const Mesh& Object3D::getMesh() const { return m_mesh; }