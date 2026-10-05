#pragma once

#include "RHI/Shader.h"
#include "RHI/VertexArray.h"

namespace Kili
{
    class Mesh
    {
    private:
        std::string mPath;
        std::shared_ptr<VertexArray> mVertexArray;
    
    public:
        Mesh() = delete;
        explicit Mesh(std::string path);

        [[nodiscard]] bool isLoaded() const { return mVertexArray != nullptr; }
        
        [[nodiscard]] std::string getPath() const { return mPath; }
        [[nodiscard]] std::shared_ptr<VertexArray> getVertexArray() const { return mVertexArray; }
        
        static std::unique_ptr<Mesh> create(const std::string& path) { return std::make_unique<Mesh>(path); }
    };
}
