#pragma once
#include "Kili/CameraManager.h"
#include "Kili/Core/Events/Event.h"

#include "Kili/Rendering/RenderCommand.h"
#include "Kili/Rendering/RHI/Shader.h"

//ADDAPI
namespace Kili
{
    class Renderer
    {     
    private:
        static glm::vec2 mScreenSize;
        
        static glm::mat4 mViewMatrix;
        static glm::mat4 mProjMatrix;
        static glm::mat4 mViewProjMatrix;
        
    public:
        static void onEvent(const IEvent& event);
        
        static GraphicApi getApi() { return RenderCommand::getApi(); }
        static std::string getApiName() { return toString(RenderCommand::getApi()); }
        
        static void resizeRenderer(uint32_t width, uint32_t height);
        static glm::vec2 getScreenSize() { return mScreenSize; }
        
        static void beginScene(const std::shared_ptr<Camera>& camera);
        static void endScene();
        
        static void submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const WorldTransform& transform);
        
    };    
}
