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
    
    struct BufferElement
    {
        std::string name;
        ShaderDataType type;
        int size;
        int offset;
        bool normalized;
        
        BufferElement() = default;
        
        BufferElement(std::string name, const ShaderDataType type, const bool normalized = false) : 
            name(std::move(name)), type(type), 
            size(ShaderDataTypeSize(type)), offset(0),
            normalized(normalized)
        {
        }
    };
    
    class BufferLayout
    {
    private:
        std::vector<BufferElement> mElements;
        int mStride;
        
        void calculateOffsetAndStride()
        {
            int offset = 0;
            mStride = 0;
            
            for (auto& element : mElements)
            {
                element.offset = offset;
                offset += element.size;
            }
            
            mStride = offset;
        }
        
    public:
        BufferLayout() = default;
        
        BufferLayout(const std::initializer_list<BufferElement>& elements) : 
            mElements(elements)
        {
            calculateOffsetAndStride();
        }
        
        [[nodiscard]] const std::vector<BufferElement>& getElements() const { return mElements; }
        
        [[nodiscard]] int getStride() const { return mStride; }
        
        std::vector<BufferElement>::const_iterator begin() const { return mElements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return mElements.end(); }
    };
}