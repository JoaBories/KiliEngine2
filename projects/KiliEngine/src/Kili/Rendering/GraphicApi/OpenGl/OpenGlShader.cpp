#include "klpch.h"
#include "OpenGlShader.h"

unsigned int Kili::OpenGlShader::compileShader(const ShaderType shaderType, const std::string& code) const
{
    int glShaderType = 0;
    switch (shaderType)
    {
        case ShaderType::Vertex : glShaderType = GL_VERTEX_SHADER; break;
        case ShaderType::TessControl : glShaderType = GL_TESS_CONTROL_SHADER; break;
        case ShaderType::TessEval : glShaderType = GL_TESS_EVALUATION_SHADER; break;
        case ShaderType::Geometry : glShaderType = GL_GEOMETRY_SHADER; break;
        case ShaderType::Fragment: glShaderType = GL_FRAGMENT_SHADER; break;
    }

    const unsigned int id = glCreateShader(glShaderType);
    const GLchar* source = code.c_str();
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);
    
    int isCompiled = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
    if(!isCompiled)
    {
        int maxLength = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<char> infoLog(maxLength);
        glGetShaderInfoLog(id, maxLength, &maxLength, infoLog.data());
        
        LOG_WARNING("Error compiling " + toString(shaderType) + " Shader " + mPath + " : " + std::string(infoLog.data()));
        glDeleteShader(id);
        return 0;
    }
    
    return id;
}
Kili::OpenGlShader::OpenGlShader(std::string path) : mPath(std::move(path))
{
    mId = glCreateProgram();

    const std::vector<ShaderFile> files = ShaderFile::readGlsl(mPath);
    
    std::vector<uint32_t> shaders;
    shaders.reserve(files.size());
    
    for (const auto& file : files)
    {
        const uint32_t shaderId = compileShader(file.getType(), file.getCode());
        
        if (shaderId == 0) continue;
        
        shaders.emplace_back(shaderId);
        mShaderTypes.emplace_back(file.getType());
        
        glAttachShader(mId, shaderId);
    }
    
    glLinkProgram(mId);
    
    int isLinked = 0;
    glGetProgramiv(mId, GL_LINK_STATUS, &isLinked);
    if (!isLinked)
    {
        int maxLength = 0;
        glGetProgramiv(mId, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<char> infoLog(maxLength);
        glGetProgramInfoLog(mId, maxLength, &maxLength, infoLog.data());
        
        LOG_WARNING("Error linking Shader " + mPath + " : " + std::string(infoLog.data()));
        glDeleteProgram(mId);
        mId = 0;
        
        for (const auto shader : shaders)
        {
            glDetachShader(mId, shader);
            glDeleteShader(shader);
        }
        return;
    }

    for (const auto shader : shaders)
    {
        glDetachShader(mId, shader);
        glDeleteShader(shader);
    }
    
    LOG_LOADING("Successfully loaded Shader " + mPath);
}

Kili::OpenGlShader::~OpenGlShader()
{
    mShaderTypes.clear();
    glDeleteProgram(mId);
}

bool Kili::OpenGlShader::hasShaderType(const ShaderType type) const
{
    const auto it = std::find(mShaderTypes.begin(), mShaderTypes.end(), type);
    return it != mShaderTypes.end();
}

void Kili::OpenGlShader::use()
{
    glUseProgram(mId);
}
