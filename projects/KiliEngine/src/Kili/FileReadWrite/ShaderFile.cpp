#include "klpch.h"
#include "ShaderFile.h"

#include "Kili/Rendering/ShaderData.h"

std::vector<Kili::ShaderFile> Kili::ShaderFile::readGlsl(const std::string& path)
{
    std::ifstream file(path);
    
    if (!file.is_open())
    {
        LOG_WARNING("Shader File not found or corrupted at " + path);
        return {};
    }
        
    std::vector<ShaderFile> shaders;

    auto lastType = ShaderType::Vertex;
    auto currentType = ShaderType::Vertex;
    std::string currentCode;
        
    std::string line;
    
    while (std::getline(file, line))
    {
        bool newShader = false;
        if (line.find("#vertex") != std::string::npos) { lastType = currentType; currentType = ShaderType::Vertex; newShader = true; }
        else if (line.find("#tess_control") != std::string::npos) { lastType = currentType; currentType = ShaderType::TessControl; newShader = true; }
        else if (line.find("#tess_eval") != std::string::npos) { lastType = currentType; currentType = ShaderType::TessEval; newShader = true; }
        else if (line.find("#geometry") != std::string::npos) { lastType = currentType; currentType = ShaderType::Geometry; newShader = true; }
        else if (line.find("#fragment") != std::string::npos) { lastType = currentType; currentType = ShaderType::Fragment; newShader = true; }
        
        if (newShader)
        {
            if (!currentCode.empty())
            {
                shaders.emplace_back(lastType, currentCode);
                currentCode.clear();
            }
            continue;
        }
            
        currentCode += line + "\n";
    }
    
    // For the last shader of the file
    if (!currentCode.empty())
    {
        shaders.emplace_back(currentType, currentCode);
        currentCode.clear();
    }
        
    file.close();
    return shaders;
}