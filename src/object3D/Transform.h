#pragma once

#include "../math/Matrix.h"
#include <array>

class Transform
{
private:
    std::array<std::array<float, 3>, 3> m_transformState{};

    Mat4 m_scale{};
    Mat4 m_rotation{};
    Mat4 m_translation{};
    Mat4 m_transform{};
public:
    Transform();
    Transform(std::array<float, 3>& scale, std::array<float, 3>& rotation, std::array<float, 3>& translation);

    void scaleObject(const std::array<float, 3>& scale);
    void rotateObject(const std::array<float, 3>& rotation);
    void translateObject(const std::array<float, 3>& translation);
    void rebuildTranform();

    Mat4 getTransformMatrix() const;
    std::array<std::array<float, 3>, 3> getTransform() const;
    std::array<float, 3> getScale() const;
    std::array<float, 3> getRotation() const;
    std::array<float, 3> getTranslation() const;
};