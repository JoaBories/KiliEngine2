#pragma once

#include "Kili/Core/Logger/Log.h"

//  Shader File Format .glsl
//
//  All shaders are packed in one file.
//  Separated by #type macros.
//  Just put a #type at the beginning of a sub shader
//
//  Types :
//  #vertex
//  #tess_control
//  #tess_eval
//  #geometry
//  #fragment
//

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
        
        [[nodiscard]] static std::vector<ShaderFile> readGlsl(const std::string& path);
        [[nodiscard]] static std::vector<std::string> readShader(const std::string& path);
        
        [[nodiscard]] ShaderType getType() const { return mType; }
        [[nodiscard]] const std::string& getCode() const { return mCode; }
    };
    
    

}