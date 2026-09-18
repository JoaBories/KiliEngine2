#include "klpch.h"
#include "Renderer.h"

#include "Kili/Core/TimeClock.h"
#include "Kili/Core/Events/WindowEvent.h"

namespace Kili
{
    Vector2 Renderer::mScreenSize = Vector2();
    
    Matrix4 Renderer::mViewMatrix = Matrix4();
    Matrix4 Renderer::mProjMatrix = Matrix4();
    Matrix4 Renderer::mViewProjMatrix = Matrix4();
    
    void Renderer::onEvent(const IEvent& event)
    {
        DispatchEvent<WindowResizeEvent>(event, [](const WindowResizeEvent& e)
        {
            mScreenSize.x = static_cast<float>(e.getWidth());
            mScreenSize.y = static_cast<float>(e.getHeight());
        });
    }

    void Renderer::beginScene(const std::shared_ptr<Camera>& camera)
    {
        RenderCommand::clear(Vector4(0.45f, 0.45f, 1.0f, 1.0f));
        
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
