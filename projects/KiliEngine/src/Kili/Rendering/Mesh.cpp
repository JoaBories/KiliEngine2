#include "klpch.h"
#include "Mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION

#include "Vendor/tiny_obj_loader.h"

Kili::Mesh::Mesh(std::string path, const std::shared_ptr<Shader>& shader) :
    mPath(std::move(path)), mShader(shader)
{
}

bool Kili::Mesh::load()
{
    tinyobj::ObjReader reader;
    
    if (const tinyobj::ObjReaderConfig readerConfig; !reader.ParseFromFile(mPath, readerConfig)) {
        if (!reader.Error().empty()) {
           LOG_ERROR("TinyObjReader: " + reader.Error());
        }
        return false;
    }
    
    if (!reader.Warning().empty()) {
        LOG_WARNING("TinyObjReader: " + reader.Warning());
    }
    
    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();
    
    std::vector<float> vertices; 
    
    uint32_t indexCount = 0;
    
    for (const auto& shape : shapes)
    {
        size_t indexOffset = 0;
        
        auto& mesh = shape.mesh;
        
        // Reserve memory space so it makes fewer memory allocation
        // Assume face are always 3 vertex.
        vertices.reserve(vertices.size() + mesh.num_face_vertices.size() * 3 * 8);
        
        // iterate trough faces
        for (size_t face = 0; face < mesh.num_face_vertices.size(); face++)
        {
            // iterate trough vertices
            const size_t faceVertices = mesh.num_face_vertices[face];
            for (size_t vertex = 0; vertex < faceVertices; vertex++)
            {
                // vertex index in attrib
                auto [vertexIndex, normalIndex, texCoordIndex] = mesh.indices[indexOffset + vertex];
                
                vertices.emplace_back(attrib.vertices[3 * vertexIndex + 0]);
                vertices.emplace_back(attrib.vertices[3 * vertexIndex + 1]);
                vertices.emplace_back(attrib.vertices[3 * vertexIndex + 2]);

                // Check if `normal_index` is zero or positive. negative = no normal data
                if (normalIndex >= 0) {
                    vertices.emplace_back(attrib.normals[3 * normalIndex + 0]);
                    vertices.emplace_back(attrib.normals[3 * normalIndex + 1]);
                    vertices.emplace_back(attrib.normals[3 * normalIndex + 2]);
                }
                else
                {
                    vertices.emplace_back(0.0f);
                    vertices.emplace_back(0.0f);
                    vertices.emplace_back(0.0f);
                }

                // Check if `texcoord_index` is zero or positive. negative = no texcoord data
                if (texCoordIndex >= 0) {
                    vertices.emplace_back(attrib.texcoords[2 * texCoordIndex + 0]);
                    vertices.emplace_back(attrib.texcoords[2 * texCoordIndex + 1]);
                }
                else
                {
                    vertices.emplace_back(0.0f);
                    vertices.emplace_back(0.0f);
                }
                
                indexCount++;
            }
            indexOffset += faceVertices;
        }
    }
    
    std::shared_ptr<VertexBuffer> vertexBuffer;
    
    mVertexArray.reset(VertexArray::create());
    
    vertexBuffer.reset(VertexBuffer::create(vertices.data(), static_cast<uint32_t>(vertices.size() * sizeof(float))));
    const BufferLayout layout = {
        { "position", ShaderDataType::Float3 },
        { "normal", ShaderDataType::Float3 },
        { "uv", ShaderDataType::Float2},
    };
    vertexBuffer->setLayout(layout);
    
    mVertexArray->addVertexBuffer(vertexBuffer);
    mVertexArray->setVertexCount(indexCount);
    
    mLoaded = true;
    return true;
}

bool Kili::Mesh::unload()
{
    // This will delete them if there is no other references
    mVertexArray.reset();
    mShader.reset();
    
    mLoaded = false;
    return true;
}
