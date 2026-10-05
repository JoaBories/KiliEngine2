#pragma once

#include "Kili/Rendering/Material.h"
#include "Kili/Rendering/Mesh.h"
#include "Kili/Rendering/RHI/Shader.h"
#include "Kili/Rendering/RHI/Texture.h"

namespace Kili
{
#define ASSET_DEFINITION(assetClass) \
private:\
    static std::unordered_map<std::string, std::shared_ptr<assetClass>> m##assetClass##Map;\
    static std::shared_ptr<assetClass> mDefault##assetClass;\
public: \
    static bool load##assetClass(const std::string& path);\
    static std::shared_ptr<assetClass> get##assetClass(const std::string& path);\
    static std::shared_ptr<assetClass> getDefault##assetClass() { return mDefault##assetClass; }\
    
#define ASSET_STATICS(assetClass) \
    std::unordered_map<std::string, std::shared_ptr<assetClass>> AssetManager::m##assetClass##Map{};\
    std::shared_ptr<assetClass> AssetManager::mDefault##assetClass = nullptr;\
    
#define ASSET_IMPLEMENTATION(assetClass) \
    bool AssetManager::load##assetClass(const std::string& path)\
    {   if (m##assetClass##Map.contains(path)) return true;\
        if (std::unique_ptr<assetClass> asset = assetClass::create(path); asset && asset->isLoaded())\
        { m##assetClass##Map.emplace(path, std::move(asset)); return true; }\
        return false; }\
    \
    std::shared_ptr<assetClass> AssetManager::get##assetClass(const std::string& path)\
    { if (load##assetClass##(path)) return m##assetClass##Map.at(path); return mDefault##assetClass; }
    
    /** 
     * Asset Manager, a full static class to store loaded assets
     * You cen use it by calling get("path") which loads it if it isn't already loaded and return a reference.
     * You can also use load() which will do the same without the reference.
     * 
     * For adding new assets you can use the ASSET_DEFINITION in the .h to add storage and methods,
     * and use the ASSET_STATICS in the .cpp to init the static storages.
     * You can also use ASSET_IMPLEMENTATION for basic implementation of get and load.
     * You will still need to add the default in the init().
     * You can leave nullptr if you don't have one, at your own risk.
     * See other assets for examples.
     **/
    class AssetManager
    {
        ASSET_DEFINITION(Material)
        ASSET_DEFINITION(Mesh)
        ASSET_DEFINITION(Shader)
        ASSET_DEFINITION(Texture)
        
    public:
        /** load default asset **/
        static void init();
        
        static void close();
    };
}
