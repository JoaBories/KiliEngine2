#pragma once

//  Mat File Format .mat
//
//  Grammar :
//  - shader: type = path
//  - texture: texture = path
//  - parameters: type:name = value
//  - Comments: '#'
//  - Case Sensitive: path, types and names require case sensitivity
//  - Spaces are ignored
//  
//  Shader types :
//  vertex
//  tess_control
//  tess_eval
//  geometry
//  fragment
//
//  Supported types for parameters :
//  Bool: 0/1 or true/false
//  Float: (+/-) x.x (e(-/+)x.x)
//  Int: (+/-) x
//  Vec2: x y (x and y as float)
//  Vec3: x y z
//  Vec4: x y z w
//
//  Malformed lines are ignored and produce a warning in logs.
//  Watch for Test.mat for example.

namespace Kili
{
    class MaterialFile
    {
    private:
        std::string name;
        
        std::string mShader;
        
        // Pair name - path
        std::vector<std::pair<std::string, std::string>> mTextures;
        
        // Pair name - value
        std::vector<std::pair<std::string, bool>> mBoolParameters;
        std::vector<std::pair<std::string, int>> mIntParameters;
        std::vector<std::pair<std::string, float>> mFloatParameters;
        std::vector<std::pair<std::string, Vector2>> mVec2TextureParameters;
        std::vector<std::pair<std::string, Vector3>> mVec3TextureParameters;
        std::vector<std::pair<std::string, Vector4>> mVec4TextureParameters;
    };
}
