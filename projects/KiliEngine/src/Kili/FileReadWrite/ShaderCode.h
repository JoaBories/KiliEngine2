#pragma once

#include "Kili/Core/Logger/Log.h"

namespace Kili::ShaderCode
{
    [[nodiscard]] static std::string ReadGlsl(const std::string& path)
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
}