#include "klpch.h"
#include "AssetManager.h"

namespace Kili
{
    ASSET_STATICS(Material)
    ASSET_STATICS(Mesh)
    ASSET_STATICS(Shader)
    ASSET_STATICS(Texture)
    
    ASSET_IMPLEMENTATION(Material)
    ASSET_IMPLEMENTATION(Mesh)
    ASSET_IMPLEMENTATION(Shader)
    
    bool AssetManager::loadTexture(const std::string& path)
    {
        if (mTextureMap.contains(path)) return true;
        if (std::unique_ptr<Texture> asset = Texture::create(TextureParameter() , path); asset && asset->isLoaded())
        {
            mTextureMap.emplace(path, std::move(asset)); 
            return true;
        }
        return false;
    }

    std::shared_ptr<Texture> AssetManager::getTexture(const std::string& path)
    {
        if (loadTexture(path)) return mTextureMap.at(path);
        return mDefaultTexture;
    }

    void AssetManager::init()
    {
        mDefaultShader = Shader::create("resources/default/default.shader");
        mDefaultTexture = Texture::create(TextureParameter(), "resources/default/default.png");
        mDefaultMaterial = nullptr;
        mDefaultMesh = Mesh::create("resources/default/cube.obj");
    }

    void AssetManager::close()
    {
        mDefaultMaterial.reset();
        mDefaultMesh.reset();
        mDefaultShader.reset();
        mDefaultTexture.reset();
        
        mMaterialMap.clear();
        mMeshMap.clear();
        mShaderMap.clear();
        mTextureMap.clear();
    }
}
