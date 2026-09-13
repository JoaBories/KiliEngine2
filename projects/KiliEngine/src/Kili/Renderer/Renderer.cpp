#include "klpch.h"
#include "Renderer.h"

void Kili::Renderer::beginScene()
{
}

void Kili::Renderer::endScene()
{
}

void Kili::Renderer::submit(const std::shared_ptr<VertexArray>& vertexArray)
{
    RenderCommand::drawIndexed(vertexArray);
}