#include "klpch.h"
#include "Renderer.h"

void Kili::Renderer::beginScene()
{
    RenderCommand::clear(Vector4(0.05f, 0.05f, 0.05f, 1.0f));
}

void Kili::Renderer::endScene()
{
}

void Kili::Renderer::submit(const std::shared_ptr<VertexArray>& vertexArray)
{
    RenderCommand::drawIndexed(vertexArray);
}