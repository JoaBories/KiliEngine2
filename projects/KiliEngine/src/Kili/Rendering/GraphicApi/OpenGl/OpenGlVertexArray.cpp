#include "klpch.h"
#include "OpenGlVertexArray.h"

#include "Kili/Rendering/GraphicApi/OpenGl/OpenGLShader.h"

#pragma region Vertex buffer

Kili::OpenGlVertexBuffer::OpenGlVertexBuffer(const float* vertices, const Uint32 size)
{
    glCreateBuffers(1, &mId);
    glBindBuffer(GL_ARRAY_BUFFER, mId);
    
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

Kili::OpenGlVertexBuffer::~OpenGlVertexBuffer()
{
    glDeleteBuffers(1, &mId);
}

void Kili::OpenGlVertexBuffer::use() const
{
    glBindBuffer(GL_ARRAY_BUFFER, mId);
}

#pragma endregion

#pragma region IndexBuffer

Kili::OpenGlIndexBuffer::OpenGlIndexBuffer(const Uint32* indices, const Uint32 count) :
    mIndexCount(count)
{
    glCreateBuffers(1, &mId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned long), indices, GL_STATIC_DRAW);
}

Kili::OpenGlIndexBuffer::~OpenGlIndexBuffer()
{
    glDeleteBuffers(1, &mId);
}

void Kili::OpenGlIndexBuffer::use() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);
}

#pragma endregion

#pragma region VertexArray

Kili::OpenGlVertexArray::OpenGlVertexArray()
{
    glCreateVertexArrays(1, &mId);
}

void Kili::OpenGlVertexArray::use() const
{
    glBindVertexArray(mId);
}

void Kili::OpenGlVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
    if (vertexBuffer->getLayout().getElements().empty()) LOG_WARNING("Vertex buffer has no layout");
    
    glBindVertexArray(mId);
    vertexBuffer->use();
    
    Uint32 index = 0;
    for (const auto& element : vertexBuffer->getLayout())
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, 
            ShaderDataTypeCount(element.type), ShaderDataTypeToOpenGl(element.type), 
            element.normalized ? GL_TRUE : GL_FALSE, vertexBuffer->getLayout().getStride(), 
            reinterpret_cast<const void*>(element.offset));
            
        index++;
    }
    
    mVertexBuffers.push_back(vertexBuffer);
}

void Kili::OpenGlVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
    glBindVertexArray(mId);
    indexBuffer->use();
    
    mIndexBuffer = indexBuffer;
}

#pragma endregion