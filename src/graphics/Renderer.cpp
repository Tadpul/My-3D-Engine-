#include <iostream>
#include <vector>
#include "../math/Vector.h"
#include "Renderer.h"

void Renderer::DrawMesh(Mesh mesh, const Mat4& transform, SDL_Renderer* sdl_renderer)
{
    for (Vec4& vertex : mesh.vertices) { vertex = (transform * vertex) * (1 / vertex.w()); }
    for (Face& face : mesh.faces)
    {
        SDL_RenderLine(sdl_renderer, mesh.vertices[face.v0].x(), mesh.vertices[face.v0].y(), mesh.vertices[face.v1].x(), mesh.vertices[face.v1].y());
        SDL_RenderLine(sdl_renderer, mesh.vertices[face.v0].x(), mesh.vertices[face.v0].y(), mesh.vertices[face.v2].x(), mesh.vertices[face.v2].y());
        SDL_RenderLine(sdl_renderer, mesh.vertices[face.v1].x(), mesh.vertices[face.v1].y(), mesh.vertices[face.v2].x(), mesh.vertices[face.v2].y());
    }
}
