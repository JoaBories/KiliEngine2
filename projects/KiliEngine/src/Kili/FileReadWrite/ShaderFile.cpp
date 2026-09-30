#include "klpch.h"
#include "ShaderFile.h"

#include "Kili/Rendering/ShaderData.h"

std::string Kili::ShaderFile::readCode(const std::string& path)
{
    std::ifstream file(path);
    
    if (!file.is_open())
    {
        LOG_WARNING("Shader File not found or corrupted at " + path);
        return {};
    }
    
    std::string line;
    std::string code;
    
    while (std::getline(file, line)) code += line + "\n";
        
    file.close();
    return code;
}

std::vector<Kili::ShaderFile> Kili::ShaderFile::readGlsl(const std::string& path)
{
    std::ifstream file(path);
    
    if (!file.is_open())
    {
        LOG_WARNING("Shader File not found or corrupted at " + path);
        return {};
    }
        
    std::vector<ShaderFile> shaders;
    std::string line;
    
    while (std::getline(file, line))
    {
        if (const size_t pos = line.find_last_of('.'); pos != std::string::npos)
        {
            const std::string extension = line.substr(pos, line.length());
            if (!isSupportedExtension(extension))
            {
                LOG_WARNING("Unknown extension " + extension + " in shader file : " + path);
                continue;
            }
            
            const ShaderType type = getShaderTypeFromExtension(extension);
            const std::string code = readCode(line);
            
            shaders.emplace_back(type, code);
        }
    }
        
    file.close();
    return shaders;
}

bool Kili::ShaderFile::isSupportedExtension(const std::string& extension)
{
    return extension == ".vert" || extension == ".tesc" || extension == ".tese" || extension == ".geom" || extension == ".frag";
}

Kili::ShaderType Kili::ShaderFile::getShaderTypeFromExtension(const std::string& extension)
{
    if (extension == ".vert") return ShaderType::Vertex;
    if (extension == ".tesc") return ShaderType::TessControl;
    if (extension == ".tese") return ShaderType::TessEval;
    if (extension == ".geom") return ShaderType::Geometry;
    if (extension == ".frag") return ShaderType::Fragment;
    return ShaderType::Vertex;
}