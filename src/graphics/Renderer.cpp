#include "../math/Vector.h"
#include "Renderer.h"

Vec2 Renderer::NDCToScreen(const Vec4& ndc, int width, int height)
{
    Vec2 result{};
    result.x() = (ndc .x() + 1) * 0.5 * width;
    result.y() = (-ndc.y() + 1) * 0.5 * height;

    return result;
}

void Renderer::DrawMesh(Mesh& mesh, const Mat4& transform, SDL_Renderer* sdl_renderer, int width, int height)
{
    std::vector<Vec4> ndcVertices{}; 
    std::vector<Vec2> sdlVertices{};
    ndcVertices.reserve(mesh.vertices.size());
    sdlVertices.reserve(mesh.vertices.size());
    for (const Vec4& vertex : mesh.vertices)
    {
        // transforms world mesh coordinates into NDC homogenus coordinates
        Vec4 clip{ transform * vertex };
        if (clip.w()) { clip = clip * (1 / clip.w()); }
        ndcVertices.push_back(clip);
    }

    for (const Vec4& ndcVertex : ndcVertices) { sdlVertices.push_back(NDCToScreen(ndcVertex, width, height)); }
    for (const Face& face : mesh.faces)
    {
        SDL_RenderLine(sdl_renderer, sdlVertices[face.v0].x(), sdlVertices[face.v0].y(), sdlVertices[face.v1].x(), sdlVertices[face.v1].y());
        SDL_RenderLine(sdl_renderer, sdlVertices[face.v0].x(), sdlVertices[face.v0].y(), sdlVertices[face.v2].x(), sdlVertices[face.v2].y());
        SDL_RenderLine(sdl_renderer, sdlVertices[face.v1].x(), sdlVertices[face.v1].y(), sdlVertices[face.v2].x(), sdlVertices[face.v2].y());
    }
}