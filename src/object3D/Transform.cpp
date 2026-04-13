#include "Transform.h"
#include <array>
#include <initializer_list>

Transform::Transform() : m_transform(Mat4::identity()) {}
Transform::Transform(std::array<float, 3>& scale, std::array<float, 3>& rotation, std::array<float, 3>& translation)
{
    m_transformState[0] = scale;
    m_transformState[1] = rotation;
    m_transformState[2] = translation;

    m_scale = Mat4::scale(scale[0], scale[1], scale[2]);
    m_rotation = Mat4::rotateX(rotation[0]) * 
                 Mat4::rotateY(rotation[1]) * 
                 Mat4::rotateZ(rotation[2]);
    m_translation = Mat4::translate(translation[0], translation[1], translation[2]);

    rebuildTranform();
}

void Transform::scaleObject(std::array<float, 3>& scale)
{
    m_transformState[0] = scale;
    m_scale = Mat4::scale(scale[0], scale[1], scale[2]);

    rebuildTranform();
}

void Transform::rotateObject(std::array<float, 3>& rotation)
{
    m_transformState[1] = rotation;
    m_rotation = Mat4::rotateX(rotation[0]) *
                 Mat4::rotateY(rotation[1]) *
                 Mat4::rotateZ(rotation[2]);

    rebuildTranform();
}

void Transform::translateObject(std::array<float, 3>& translation)
{
    m_transformState[2] = translation;
    m_translation = Mat4::scale(translation[0], translation[1], translation[2]);

    rebuildTranform();
}

void Transform::rebuildTranform() { m_transform = m_translation * m_scale * m_rotation; }

Mat4 Transform::getTransformMatrix() const { return m_transform; }

std::array<std::array<float, 3>, 3> Transform::getTransform() const { return m_transformState; }

std::array<float, 3> Transform::getScale() const { return m_transformState[0]; }
std::array<float, 3> Transform::getRotation() const { return m_transformState[1]; }
std::array<float, 3> Transform::getTranslation() const { return m_transformState[2]; }
