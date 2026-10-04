#pragma once

//  Mat File Format .mat
//
//  Grammar :
//  - shader: shader = path
//  - texture: texture = path
//  - parameters: type:name = value
//  - Comments: '#'
//  - Case Sensitive: path, types and names require case sensitivity
//  - Spaces and quotes are ignored
//  - Support multiple textures but only one shader. A second shader will override the first.
//
//  Supported types for parameters :
//  bool: 0/1 or true/false
//  float: (+/-) x.x (e(-/+)x.x)
//  int: (+/-) x
//  vec2: x y (x and y as float)
//  vec3: x y z
//  vec4: x y z w
//
//  Malformed lines are ignored and produce a warning in logs.
//  Watch for Test.mat for example.

namespace Kili
{
    class MaterialFile
    {
        std::string mShader;
        
        // Pair name - path
        std::vector<std::string> mTextures;
        
        // Pair name - value
        std::vector<std::pair<std::string, bool>> mBoolParameters;
        std::vector<std::pair<std::string, int>> mIntParameters;
        std::vector<std::pair<std::string, float>> mFloatParameters;
        std::vector<std::pair<std::string, Vector2>> mVec2Parameters;
        std::vector<std::pair<std::string, Vector3>> mVec3Parameters;
        std::vector<std::pair<std::string, Vector4>> mVec4Parameters;
        
        static bool handleTypes(const std::string& type, const std::string& value, const std::string& paramName, MaterialFile& material);
        
    public:
        MaterialFile() = default;
        
        void setShader(std::string shader)                                  { mShader = std::move(shader); }
        [[nodiscard]] const std::string& getShader() const                  { return mShader; }
        
        void addTexture(std::string texture)                                { mTextures.emplace_back(std::move(texture)); }
        [[nodiscard]] const std::vector<std::string>& getTextures() const   { return mTextures; }
        
        void addBoolParameter(std::string name, bool value)     { mBoolParameters.emplace_back(std::move(name), value); }
        void addIntParameter(std::string name, int value)       { mIntParameters.emplace_back(std::move(name), value); }
        void addFloatParameter(std::string name, float value)   { mFloatParameters.emplace_back(std::move(name), value); }
        void addVec2Parameter(std::string name, Vector2 value)  { mVec2Parameters.emplace_back(std::move(name), value); }
        void addVec3Parameter(std::string name, Vector3 value)  { mVec3Parameters.emplace_back(std::move(name), value); }
        void addVec4Parameter(std::string name, Vector4 value)  { mVec4Parameters.emplace_back(std::move(name), value); }
        
        [[nodiscard]] const std::vector<std::pair<std::string, bool>>& getBoolParameters() const    { return mBoolParameters; }
        [[nodiscard]] const std::vector<std::pair<std::string, int>>& getIntParameters() const      { return mIntParameters; }
        [[nodiscard]] const std::vector<std::pair<std::string, float>>& getFloatParameters() const  { return mFloatParameters; }
        [[nodiscard]] const std::vector<std::pair<std::string, Vector2>>& getVec2Parameters() const { return mVec2Parameters; }
        [[nodiscard]] const std::vector<std::pair<std::string, Vector3>>& getVec3Parameters() const { return mVec3Parameters; }
        [[nodiscard]] const std::vector<std::pair<std::string, Vector4>>& getVec4Parameters() const { return mVec4Parameters; }
        
        static MaterialFile readMaterial(const std::string& path);
    };
}
