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
    const tinyobj::ObjReaderConfig readerConfig;
    tinyobj::ObjReader reader;
    
    if (!reader.ParseFromFile(mPath, readerConfig)) {
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
    std::vector<uint32_t> indices;
    
    uint32_t indiceCount = 0;
    for (size_t shape = 0; shape < shapes.size(); shape++)
    {
        size_t indexOffset = 0;
        
        auto& mesh = shapes[shape].mesh;
        vertices.reserve(mesh.num_face_vertices.size() * 3 * 8);
        
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
                
                indices.emplace_back(indiceCount);
                indiceCount++;
            }
            indexOffset += faceVertices;
        }
    }
    
    std::shared_ptr<VertexBuffer> vertexBuffer;
    std::shared_ptr<IndexBuffer> indexBuffer;
    
    mVertexArray.reset(VertexArray::create());
    
    vertexBuffer.reset(VertexBuffer::create(vertices.data(), vertices.size() * sizeof(float)));
    BufferLayout layout = {
        { "position", ShaderDataType::Float3 },
        { "normal", ShaderDataType::Float3 },
        { "uv", ShaderDataType::Float2},
    };
    vertexBuffer->setLayout(layout);
    
    indexBuffer.reset(IndexBuffer::create(indices.data(), indiceCount - 1));
    
    mVertexArray->addVertexBuffer(vertexBuffer);
    mVertexArray->setIndexBuffer(indexBuffer);
    
    mLoaded = true;
    return true;
}

bool Kili::Mesh::unload()
{
    mLoaded = false;
    return true;
}
