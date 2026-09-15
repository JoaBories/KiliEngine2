#pragma once
#include "Kili/CameraManager.h"
#include "Kili/Core/Events/Event.h"

#include "Kili/Renderer/RenderCommand.h"
#include "RHI/Shader.h"

//ADDAPI
namespace Kili
{
    class Renderer
    {     
    private:
        static Vector2 mScreenSize;
        
        static Matrix4 mViewMatrix;
        static Matrix4 mProjMatrix;
        static Matrix4 mViewProjMatrix;
        
    public:
        static void onEvent(const IEvent& event);
        
        static GraphicApi getApi() { return RenderCommand::getApi(); }
        static std::string getApiName() { return toString(RenderCommand::getApi()); }
        
        static Vector2 getScreenSize() { return mScreenSize; }
        
        static void beginScene(const std::shared_ptr<Camera>& camera);
        static void endScene();
        
        static void submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const Matrix4& transformMatrix);
        
    };
}
