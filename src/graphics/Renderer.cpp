#include "../math/Vector.h"
#include "Renderer.h"
#include "line/ClipLine.h"

void meshToNDC(Object3D& object, std::vector<Vec4>& ndcVertices, int width, int height)
{
    // projects matrix so that we can scale the window
    float aspect = static_cast<float>(width) / static_cast<float>(height);
    Mat4 projection{ Mat4::projection(90.0f, aspect, 1.0f, 100.0f) };
    Mat4 fullTransform = projection
                       * object.getWorldTransform().getTransformMatrix()
                       * object.getLocalTransform().getTransformMatrix();

    for (const Vec4& vertex : object.getMesh().vertices)
    {
        Vec4 clip{ fullTransform * vertex };
        
        if (std::abs(clip.w()) > 1e-6f) { clip = clip * (1 / clip.w()); }
        else std::cout << "w is 0";
        ndcVertices.push_back(clip);
    }
}

Vec2 NDCToScreen(const Vec4& ndc, int width, int height)
{
    Vec2 result{};
    result.x() = (ndc.x() + 1) * 0.5f * width;
    result.y() = (-ndc.y() + 1) * 0.5f * height;

    return result;
}

void drawObject(Object3D& object, SDL_Renderer* sdl_renderer, Framebuffer& fb, const std::string& type, bool backFaceCulling) 
{
    assert((type == "wireframe" || type == "object") && "Error: object type must be valid");
    std::vector<Vec4> ndcVertices{}; 
    std::vector<Vec2> sdlVertices{};
    ndcVertices.reserve(object.getMesh().vertices.size());
    sdlVertices.reserve(object.getMesh().vertices.size());
    
    meshToNDC(object, ndcVertices, fb.width, fb.height);

    // turns ndc vertices to sdl verices
    for (const Vec4& ndcVertex : ndcVertices) { sdlVertices.push_back(NDCToScreen(ndcVertex, fb.width, fb.height)); }

    // for each face draw, and apply backFaceCulling if selected
    for (const Face& face : object.getMesh().faces)
    {
        if (backFaceCulling)
        {
            Vec4 Vec1 = ndcVertices[face.v1] - ndcVertices[face.v0];
            Vec4 Vec2 = ndcVertices[face.v2] - ndcVertices[face.v1];
            if (Vec4::crossProduct(Vec1, Vec2).z() < -1e-6f) continue;
        }

        if (type == "wireframe")
        {
            drawClippedLine(fb, sdlVertices[face.v0].x(), sdlVertices[face.v0].y(), sdlVertices[face.v1].x(), sdlVertices[face.v1].y(), 0xFFFFFFFF);
            drawClippedLine(fb, sdlVertices[face.v0].x(), sdlVertices[face.v0].y(), sdlVertices[face.v2].x(), sdlVertices[face.v2].y(), 0xFFFFFFFF);
            drawClippedLine(fb, sdlVertices[face.v1].x(), sdlVertices[face.v1].y(), sdlVertices[face.v2].x(), sdlVertices[face.v2].y(), 0xFFFFFFFF);
        }
        else if (type == "object");
    }
}