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
        
        LOG_WARNING("Error compiling " + toString(shaderType) + " Shader " + mName + " : " + std::string(infoLog.data()));
        
        glDeleteShader(id);
        
        return 0;
    }
    
    LOG_LOADING("Successfully loaded " + toString(shaderType) + " Shader " + mName);
    
    return id;
}

Kili::OpenGlShader::~OpenGlShader()
{
    OpenGlShader::unload();
}

bool Kili::OpenGlShader::load()
{
    if (mLoaded) return false;
    
    mId = glCreateProgram();
    
    std::vector<unsigned int> shaders;
    shaders.reserve(mPaths.size());
    
    for (const auto& [type, path] : mPaths)
    {
        const unsigned int shader = compileShader(type, ShaderCode::ReadGlsl(path));
        if (shader == 0) continue;
        shaders.emplace_back(shader);
        glAttachShader(mId, shader);
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
        
        LOG_WARNING("Error linking Shader " + mName + " : " + std::string(infoLog.data()));
        
        glDeleteProgram(mId);
        
        for (const auto shader : shaders)
        {
            glDetachShader(mId, shader);
            glDeleteShader(shader);
        }
        
        mLoaded = false;
        return false;
    }

    for (const auto shader : shaders)
    {
        glDetachShader(mId, shader);
        glDeleteShader(shader);
    }
    
    shaders.clear();
    
    LOG_LOADING("Successfully loaded Shader " + mName);
    
    mLoaded = true;
    return true;
}

bool Kili::OpenGlShader::unload()
{
    if (!mLoaded) return false;
    
    glDeleteProgram(mId);
    
    mLoaded = false;
    return true;
}

void Kili::OpenGlShader::setActive()
{
    glUseProgram(mId);
}