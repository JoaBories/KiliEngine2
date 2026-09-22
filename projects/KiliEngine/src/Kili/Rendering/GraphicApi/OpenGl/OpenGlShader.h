#pragma once
#include "Kili/Rendering/RHI/Shader.h"

namespace Kili
{
    static GLenum ShaderDataTypeToOpenGl(const ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float : return GL_FLOAT;
            case ShaderDataType::Float2 : return GL_FLOAT;
            case ShaderDataType::Float3 : return GL_FLOAT;
            case ShaderDataType::Float4 : return GL_FLOAT;
            case ShaderDataType::Mat3 : return GL_FLOAT;
            case ShaderDataType::Mat4 : return GL_FLOAT;
            case ShaderDataType::Int : return GL_INT;
            case ShaderDataType::Int2 : return GL_INT;
            case ShaderDataType::Int3 : return GL_INT;
            case ShaderDataType::Int4 : return GL_INT;
            case ShaderDataType::Bool : return GL_BOOL;
        }
        
        LOG_WARNING("Unknown ShaderDataType");
        return 0;
    }
    
    class OpenGlShader : public Shader
    {
    private:
        std::string mName;
        std::vector<ShaderType> mShaderTypes;
        uint32_t mId;
    
        /** Compile shader and return the shader id, debug shader errors in warnings **/
        [[nodiscard]] unsigned int compileShader(ShaderType shaderType, const std::string& code) const;
        
    public:
        OpenGlShader(std::string name, const std::vector<std::string>& paths);
        
        ~OpenGlShader() override;
        
        [[nodiscard]] bool hasShaderType(ShaderType type) const override;
        [[nodiscard]] std::string getName() const override { return mName; }
        
        void use() override;
        
        // uniforms
        void setBool(const std::string& pName, const bool value) override       { glUniform1i(glGetUniformLocation(mId, pName.c_str()), value); }
        void setInt(const std::string& pName, const int value) override         { glUniform1i(glGetUniformLocation(mId, pName.c_str()), value); }
        void setFloat(const std::string& pName, const float value) override     { glUniform1f(glGetUniformLocation(mId, pName.c_str()), value); }
        void setVec2(const std::string& pName, const Vector2& value) override   { glUniform2f(glGetUniformLocation(mId, pName.c_str()), value.x, value.y); }
        void setVec3(const std::string& pName, const Vector3& value) override   { glUniform3f(glGetUniformLocation(mId, pName.c_str()), value.x, value.y, value.z); }
        void setVec4(const std::string& pName, const Vector4& value) override   { glUniform4f(glGetUniformLocation(mId, pName.c_str()), value.x, value.y, value.z, value.w); }
        void setMat4(const std::string& pName, const Matrix4& matrix) override  { glUniformMatrix4fv(glGetUniformLocation(mId, pName.c_str()), 1, GL_TRUE, matrix.asFloatPtr()); }
        
        void uploadBool(const int location, const bool value) override          { glUniform1i(location, value); }
        void uploadInt(const int location, const int value) override            { glUniform1i(location, value); }
        void uploadFloat(const int location, const float value) override        { glUniform1f(location, value); }
        void uploadVec2(const int location, const Vector2& value) override      { glUniform2f(location, value.x, value.y); }
        void uploadVec3(const int location, const Vector3& value) override      { glUniform3f(location, value.x, value.y, value.z); }
        void uploadVec4(const int location, const Vector4& value) override      { glUniform4f(location, value.x, value.y, value.z, value.w); }
        void uploadMat4(const int location, const Matrix4& matrix) override     { glUniformMatrix4fv(location, 1, GL_TRUE, matrix.asFloatPtr()); }
    };
}