#include "klpch.h"
#include "Renderer.h"

#include "Kili/Core/TimeClock.h"
#include "Kili/Core/Events/WindowEvent.h"

namespace Kili
{
    glm::vec2 Renderer::mScreenSize = glm::vec2();
    
    glm::mat4 Renderer::mViewMatrix = glm::mat4();
    glm::mat4 Renderer::mProjMatrix = glm::mat4();
    glm::mat4 Renderer::mViewProjMatrix = glm::mat4();
    
    void Renderer::onEvent(const IEvent& event)
    {
    }

    void Renderer::resizeRenderer(const uint32_t width, const uint32_t height)
    {
        mScreenSize.x = static_cast<float>(width);
        mScreenSize.y = static_cast<float>(height);
        
        RenderCommand::resizeRenderBuffer(width, height);
    }
    
    void Renderer::beginScene(const std::shared_ptr<Camera>& camera)
    {
        RenderCommand::clear(glm::vec4(0.45f, 0.45f, 1.0f, 1.0f));
        
        if (!camera)
        {
            LOG_WARNING("There is no camera");
            return;
        }
        
        camera->recalculate();
        mViewMatrix = camera->getViewMatrix();
        mProjMatrix = camera->getProjMatrix();
        mViewProjMatrix = camera->getViewProjMatrix();
    }

    void Renderer::endScene()
    {
    }

    void Renderer::submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const WorldTransform& transform)
    {
        shader->use();
        shader->setMat4("uViewProjMatrix", mViewProjMatrix);
        shader->setMat4("uTransform", transform.getTransformMatrix());
        shader->setFloat("uTime", static_cast<float>(TimeClock::time()));
    
        if (vertexArray->getIndexBuffer()) RenderCommand::drawIndexed(vertexArray);
        if (vertexArray->getVertexCount()) RenderCommand::draw(vertexArray);
    }
}
