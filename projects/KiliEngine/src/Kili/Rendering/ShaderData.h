#pragma once
#include "Kili/Core/Logger/Log.h"

namespace Kili
{
    enum class ShaderDataType : Uint8
    {
        None = 0,
        Float, Float2, Float3, Float4,
        Mat3, Mat4,
        Int, Int2, Int3, Int4,
        Bool
    };
    
    static int ShaderDataTypeSize(const ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:     return 4;
            case ShaderDataType::Float2:    return 4 * 2;
            case ShaderDataType::Float3:    return 4 * 3;
            case ShaderDataType::Float4:    return 4 * 4;
            case ShaderDataType::Mat3:      return 4 * 3 * 3;
            case ShaderDataType::Mat4:      return 4 * 4 * 4;
            case ShaderDataType::Int:       return 4;
            case ShaderDataType::Int2:      return 4 * 2;
            case ShaderDataType::Int3:      return 4 * 3;
            case ShaderDataType::Int4:      return 4 * 4;
            case ShaderDataType::Bool:      return 1;
            default: break;
        }
        
        LOG_WARNING("Unknown ShaderDataType");
        return 0;
    }
    
    static int ShaderDataTypeCount(const ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:     return 1;
            case ShaderDataType::Float2:    return 2;
            case ShaderDataType::Float3:    return 3;
            case ShaderDataType::Float4:    return 4;
            case ShaderDataType::Mat3:      return 3 * 3;
            case ShaderDataType::Mat4:      return 4 * 4;
            case ShaderDataType::Int:       return 1;
            case ShaderDataType::Int2:      return 2;
            case ShaderDataType::Int3:      return 3;
            case ShaderDataType::Int4:      return 4;
            case ShaderDataType::Bool:      return 1;
            default: break;
        }
        
        LOG_WARNING("Unknown ShaderDataType");
        return 0;
    }
    
    enum class ShaderType : char
    {
        Vertex,
        TessControl,
        TessEval,
        Geometry,
        Fragment
    };
    
    inline std::string toString(const ShaderType e)
    {
        switch (e)
        {
            case ShaderType::Vertex: return "Vertex";
            case ShaderType::TessControl: return "TessControl";
            case ShaderType::TessEval: return "TessEval";
            case ShaderType::Geometry: return "Geometry";
            case ShaderType::Fragment: return "Fragment";
        }
        
        return "unknow";
    }
}
