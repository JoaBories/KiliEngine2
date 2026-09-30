#pragma once

#include "Kili/Core/Logger/Log.h"

//  Shader File Format .shader
//
//  A file giving a path for each shader composing a shader program 
//
//  Types :
//  .vert
//  .tesc
//  .tese
//  .geom
//  .frag

namespace Kili
{
    enum class ShaderType : char;

    class ShaderFile
    {
    private:
        ShaderType mType;
        std::string mCode;
        
    public:
        ShaderFile() = default;
        ShaderFile(const ShaderType type, std::string code) : mType(type), mCode(std::move(code)) {}
        
        [[nodiscard]] ShaderType getType() const { return mType; }
        [[nodiscard]] const std::string& getCode() const { return mCode; }
        
        // statics
    private:
        [[nodiscard]] static std::string readCode(const std::string& path);
        
    public:
        [[nodiscard]] static std::vector<ShaderFile> readGlsl(const std::string& path);
        [[nodiscard]] static bool isSupportedExtension(const std::string& extension);
        [[nodiscard]] static ShaderType getShaderTypeFromExtension(const std::string& extension);
    };
    
    

}