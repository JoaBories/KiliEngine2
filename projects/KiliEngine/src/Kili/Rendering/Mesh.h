#pragma once

#include "Kili/AssetManager/Asset.h"
#include "RHI/Shader.h"
#include "RHI/VertexArray.h"

namespace Kili
{
    class Mesh : public IAsset
    {
    private:
        std::string mPath;
        std::shared_ptr<Shader> mShader;
        std::shared_ptr<VertexArray> mVertexArray;
    
    public:
        Mesh() = delete;
        Mesh(std::string path, const std::shared_ptr<Shader>& shader);
        
        bool load() override;
        bool unload() override;
        
        [[nodiscard]] std::string getPath() const { return mPath; }
        
        [[nodiscard]] std::shared_ptr<Shader> getShader() const { return mShader; }
        void setShader(const std::shared_ptr<Shader>& shader) { mShader = shader; }
        
        [[nodiscard]] std::shared_ptr<VertexArray> getVertexArray() const { return mVertexArray; }
    };
}
