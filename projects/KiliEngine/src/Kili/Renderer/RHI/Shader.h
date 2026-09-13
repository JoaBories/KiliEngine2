#pragma once

#include "Kili/AssetManager/Asset.h"
#include "Kili/FileReadWrite/ShaderCode.h"

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
            default: return "unknown";
        }
    }

    class Shader : public IAsset
    {
    protected:
        std::string mName;
        std::unordered_map<ShaderType, std::string> mPaths;
    
    public:
        Shader(std::string name, const std::vector<std::string>& paths) :
            mName(std::move(name))
        {
            for (auto path : paths)
            {
                if (const size_t pos = path.find_last_of('.'); pos != std::string::npos)
                {
                    mPaths[getShaderTypeFromExtension(path.substr(pos, path.length()))] = path;
                }
            }
        }
    
        [[nodiscard]] std::string getPath(const ShaderType type) const { if (mPaths.find(type) != mPaths.end()) return mPaths.at(type); else return ""; }
        [[nodiscard]] bool hasShaderType(const ShaderType type) const { return mPaths.find(type) != mPaths.end(); }
        
        virtual void use() = 0;
        
        // uniform functions
        virtual void setBool(const std::string& pName, bool pValue) = 0;
        virtual void setInt(const std::string& pName, int pValue) = 0;
        virtual void setFloat(const std::string& pName, float pValue) = 0;
        virtual void setVec2(const std::string& pName, const Vector2& pValue) = 0;
        virtual void setVec3(const std::string& pName, const Vector3& pValue) = 0;
        virtual void setVec4(const std::string& pName, const Vector4& pValue) = 0;
        virtual void setMat4(const std::string& pName, const Matrix4& pMatrix) = 0;
        
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
        
        static Shader* create(const std::string& name, const std::vector<std::string>& paths);
    };
}
