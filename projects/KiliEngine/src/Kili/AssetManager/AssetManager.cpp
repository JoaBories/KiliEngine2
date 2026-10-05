#include "klpch.h"
#include "AssetManager.h"

namespace Kili
{
    std::unordered_map<std::string, std::shared_ptr<Shader>> AssetManager::mShaders{};
    std::unordered_map<std::string, std::shared_ptr<Texture>> AssetManager::mTextures{};
    std::unordered_map<std::string, std::shared_ptr<Mesh>> AssetManager::mMeshes{};
    std::unordered_map<std::string, std::shared_ptr<Material>> AssetManager::mMaterials{};

    bool AssetManager::loadShader(const std::string& path)
    {
        if (mShaders.find(path) != mShaders.end()) return true;
        if (std::unique_ptr<Shader> asset = Shader::create(path); asset && asset->isLoaded())
        {
            mShaders.emplace(path, std::move(asset));
            return true;
        }
        return false;
    }

    bool AssetManager::loadTexture(std::string path)
    {
        return true;
    }

    bool AssetManager::loadMesh(std::string path)
    {
        return true;
    }

    bool AssetManager::loadMaterial(std::string path)
    {
        return true;
    }

    std::shared_ptr<Shader> AssetManager::getShader(std::string path)
    {
        return nullptr;
    }

    std::shared_ptr<Texture> AssetManager::getTexture(std::string path)
    {
        return nullptr;
    }

    std::shared_ptr<Mesh> AssetManager::getMesh(std::string path)
    {
        return nullptr;
    }

    std::shared_ptr<Material> AssetManager::getMaterial(std::string path)
    {
        return nullptr;
    }
}
