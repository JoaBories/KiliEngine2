#include "klpch.h"
#include "OpenGlRendererApi.h"

void Kili::OpenGlRendererApi::clear(const Vector4& clearColor)
{
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glEnable(GL_DEPTH_TEST);
}

void Kili::OpenGlRendererApi::draw(const std::shared_ptr<VertexArray>& vertexArray)
{
    glDrawArrays(GL_TRIANGLES, 0, vertexArray->getVertexCount());
}

void Kili::OpenGlRendererApi::drawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
{
    glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->count(), GL_UNSIGNED_INT, nullptr);
}

void Kili::OpenGlRendererApi::setMsaa(const int samples) const
{
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, samples);
}
