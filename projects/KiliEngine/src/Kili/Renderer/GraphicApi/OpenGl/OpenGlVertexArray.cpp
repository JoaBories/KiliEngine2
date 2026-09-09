#include "klpch.h"
#include "OpenGlVertexArray.h"

#pragma region Vertex buffer

Kili::OpenGlVertexBuffer::OpenGlVertexBuffer(const float* vertices, const unsigned long size)
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

Kili::OpenGlIndexBuffer::OpenGlIndexBuffer(const unsigned long* indices, const unsigned long count) :
    mIndiceCount(count)
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



#pragma endregion