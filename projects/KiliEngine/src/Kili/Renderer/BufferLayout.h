#pragma once
#include "Kili/Core/Logger/Log.h"

#include "Kili/Renderer/RHI/Shader.h"

namespace Kili
{
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