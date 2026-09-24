#pragma once
#include "RHI/Shader.h"
#include "RHI/Texture.h"

namespace Kili
{
    /** 
     * Material, abstracting Shader, Textures and parameters for shaders. \n
     * It loads from a .mat files that reference a set of different sub Shaders (vertex, fragment, etc.), a set of Textures and a set of Parameters by types.
     **/
    class Material : public IAsset
    {
    private:
        std::shared_ptr<Shader> mShader;
        
        // Pair location - texture
        std::vector<std::pair<int, std::shared_ptr<Texture>>> mTextures;
        
        // Pair location - value
        std::vector<std::pair<int, bool>> mBoolParameters;
        std::vector<std::pair<int, int>> mIntParameters;
        std::vector<std::pair<int, float>> mFloatParameters;
        std::vector<std::pair<int, Vector2>> mVec2TextureParameters;
        std::vector<std::pair<int, Vector3>> mVec3TextureParameters;
        std::vector<std::pair<int, Vector4>> mVec4TextureParameters;
        
    public:
        Material() = delete;
        explicit Material(std::string path);

        [[nodiscard]] std::shared_ptr<Shader> getShader() const { return mShader; }
        
        bool load() override;
        bool unload() override;
        
        void use();
    };
}