#pragma once

#include "Kili/Rendering/ShaderData.h"
#include "Kili/FileReadWrite/ShaderFile.h"

namespace Kili
{
    class Shader
    {    
    public:    
        virtual ~Shader() = default;
        
        [[nodiscard]] virtual bool hasShaderType(ShaderType type) const = 0;
        [[nodiscard]] virtual std::string getPath() const = 0;
        
        virtual void use() = 0;
        virtual bool isLoaded() = 0;
        
        // uniform functions
        virtual void setBool(const std::string& pName, bool value) = 0;
        virtual void setInt(const std::string& pName, int value) = 0;
        virtual void setFloat(const std::string& pName, float value) = 0;
        virtual void setVec2(const std::string& pName, const glm::vec2& value) = 0;
        virtual void setVec3(const std::string& pName, const glm::vec3& value) = 0;
        virtual void setVec4(const std::string& pName, const glm::vec4& value) = 0;
        virtual void setMat4(const std::string& pName, const glm::mat4& matrix) = 0;
        
        virtual void uploadBool(int location, bool value) = 0;
        virtual void uploadInt(int location, int value) = 0;
        virtual void uploadFloat(int location, float value) = 0;
        virtual void uploadVec2(int location, const glm::vec2& value) = 0;
        virtual void uploadVec3(int location, const glm::vec3& value) = 0;
        virtual void uploadVec4(int location, const glm::vec4& value) = 0;
        virtual void uploadMat4(int location, const glm::mat4& matrix) = 0;
        
        // Useful for asset manager later
        static bool isSupportedExtension(const std::string& extension) {
            return extension == ".vert" || extension == ".tesc" || extension == ".tese" || extension == ".geom" || extension == ".frag"; }
    
        static ShaderType getShaderTypeFromExtension(const std::string& extension)
        {
            if (extension == ".vert") return ShaderType::Vertex;
            if (extension == ".tesc") return ShaderType::TessControl;
            if (extension == ".tese") return ShaderType::TessEval;
            if (extension == ".geom") return ShaderType::Geometry;
            if (extension == ".frag") return ShaderType::Fragment;
            return ShaderType::Vertex;
        }
        
        static std::unique_ptr<Shader> create(const std::string& path);
    };
}
