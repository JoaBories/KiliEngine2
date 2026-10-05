#pragma once

#include "Kili/Rendering/Material.h"
#include "Kili/Rendering/Mesh.h"
#include "Kili/Rendering/RHI/Shader.h"
#include "Kili/Rendering/RHI/Texture.h"

namespace Kili
{
    class AssetManager
    {
    private:
        static std::unordered_map<std::string, std::shared_ptr<Shader>> mShaders;
        static std::unordered_map<std::string, std::shared_ptr<Texture>> mTextures;
        static std::unordered_map<std::string, std::shared_ptr<Mesh>> mMeshes;
        static std::unordered_map<std::string, std::shared_ptr<Material>> mMaterials;
        
    public:
        static bool loadShader(const std::string& path);
        static bool loadTexture(std::string path);
        static bool loadMesh(std::string path);
        static bool loadMaterial(std::string path);
        
        static std::shared_ptr<Shader> getShader(std::string path);
        static std::shared_ptr<Texture> getTexture(std::string path);
        static std::shared_ptr<Mesh> getMesh(std::string path);
        static std::shared_ptr<Material> getMaterial(std::string path);
    };
}
