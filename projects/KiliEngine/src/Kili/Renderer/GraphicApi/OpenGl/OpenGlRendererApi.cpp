#include "klpch.h"
#include "OpenGlRendererApi.h"

void Kili::OpenGlRendererApi::clear(const Vector4& clearColor)
{
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Kili::OpenGlRendererApi::drawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
{
    glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->count(), GL_UNSIGNED_INT, nullptr);
}