#pragma once
#include "Kili/Renderer/Shader.h"

namespace Kili
{
    class OpenGlShader : public Shader
    {
    private:
        unsigned int mId;
    
        /** Compile shader and return the shader id, debug shader errors in warnings **/
        [[nodiscard]] unsigned int compileShader(ShaderType shaderType, const std::string& code) const;
        
    public:
        OpenGlShader(std::string name, const std::vector<std::string>& paths) :
            Shader(std::move(name), paths), mId(0)
        {
        }
        
        ~OpenGlShader() override;
        
        bool load() override;
        bool unload() override;
        
        void setActive() override;
        
        // uniforms
        void setBool(const std::string& pName, const bool pValue) override      { glUniform1i(glGetUniformLocation(mId, pName.c_str()), pValue); }
        void setInt(const std::string& pName, const int pValue) override        { glUniform1i(glGetUniformLocation(mId, pName.c_str()), pValue); }
        void setFloat(const std::string& pName, const float pValue) override    { glUniform1f(glGetUniformLocation(mId, pName.c_str()), pValue); }
        void setVec2(const std::string& pName, const Vector2& pValue) override  { glUniform2f(glGetUniformLocation(mId, pName.c_str()), pValue.x, pValue.y); }
        void setVec3(const std::string& pName, const Vector3& pValue) override  { glUniform3f(glGetUniformLocation(mId, pName.c_str()), pValue.x, pValue.y, pValue.z); }
        void setVec4(const std::string& pName, const Vector4& pValue) override  { glUniform4f(glGetUniformLocation(mId, pName.c_str()), pValue.x, pValue.y, pValue.z, pValue.w); }
        void setMat4(const std::string& pName, const Matrix4& pMatrix) override { glUniformMatrix4fv(glGetUniformLocation(mId, pName.c_str()), 1, GL_FALSE, pMatrix.asFloatPtr()); }
    };
}