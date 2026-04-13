#include "../math/Vector.h"
#include "Renderer.h"

Vec2 Renderer::NDCToScreen(const Vec4& ndc, int width, int height)
{
    Vec2 result{};
    result.x() = (ndc.x() + 1) * 0.5f * width;
    result.y() = (-ndc.y() + 1) * 0.5f * height;

    return result;
}

void Renderer::DrawMesh(Mesh& mesh, const Mat4& transform, SDL_Renderer* sdl_renderer, int width, int height, bool backFaceCulling=true)
{
    std::vector<Vec4> ndcVertices{}; 
    std::vector<Vec2> sdlVertices{};
    ndcVertices.reserve(mesh.vertices.size());
    sdlVertices.reserve(mesh.vertices.size());
    for (const Vec4& vertex : mesh.vertices)
    {
        // projects matrix so that we can scale the window
        float aspect = static_cast<float>(width) / static_cast<float>(height);
        Mat4 projection{ Mat4::perspective(90.0f, aspect, 1.0f, 100.0f) };

        Vec4 clip{ projection * transform * vertex };
        
        if (std::abs(clip.w()) > -1e-6f) { clip = clip * (1 / clip.w()); }
        ndcVertices.push_back(clip);
    }

    for (const Vec4& ndcVertex : ndcVertices) { sdlVertices.push_back(NDCToScreen(ndcVertex, width, height)); }

    for (const Face& face : mesh.faces)
    {
        if (backFaceCulling)
        {
            Vec4 Vec1 = ndcVertices[face.v1] - ndcVertices[face.v0];
            Vec4 Vec2 = ndcVertices[face.v2] - ndcVertices[face.v1];
            if (Vec4::crossProduct(Vec1, Vec2).z() < 1e-6f) continue;
        }

        SDL_RenderLine(sdl_renderer, sdlVertices[face.v0].x(), sdlVertices[face.v0].y(), sdlVertices[face.v1].x(), sdlVertices[face.v1].y());
        SDL_RenderLine(sdl_renderer, sdlVertices[face.v0].x(), sdlVertices[face.v0].y(), sdlVertices[face.v2].x(), sdlVertices[face.v2].y());
        SDL_RenderLine(sdl_renderer, sdlVertices[face.v1].x(), sdlVertices[face.v1].y(), sdlVertices[face.v2].x(), sdlVertices[face.v2].y());
    }
}