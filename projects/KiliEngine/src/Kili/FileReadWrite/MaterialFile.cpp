#include "klpch.h"
#include "MaterialFile.h"

#include "Kili/Core/Logger/Log.h"
#include "Kili/FileReadWrite/ReadWriteUtils.h"

namespace Kili
{
    bool MaterialFile::handleTypes(const std::string& type, const std::string& value, const std::string& paramName, MaterialFile& material)
    {
        if (type == "bool")
        {
            bool val;
            try {val = Util::ToBool(value);}
            catch (std::invalid_argument const&)
            {
                LOG_WARNING("Invalid bool");
                return false;
            }
            material.addBoolParameter(paramName, val);
            return true;
        }
        
        if (type == "float")
        {
            float val;
            try { val = std::stof(value); }
            catch (std::invalid_argument const&) { 
                LOG_WARNING("Invalid float");
                return false;
            }
            material.addFloatParameter(paramName, val);
            return true;
        }
        
        if (type == "int")
        {
            int val;
            try { val = std::stoi(value); }
            catch (std::invalid_argument const&) {
                LOG_WARNING("Invalid int");
                return false;
            }
            catch (std::out_of_range const&) {
                LOG_WARNING("Integer out of range");
                return false;
            }
            material.addIntParameter(paramName, val);
            return true;
        }
        
        if (type == "vec2")
        {
            if (const std::vector<std::string> comps = Util::BreakString(value, ','); comps.size() == 2)
            {
                float val0, val1;
                try { val0 = std::stof(comps[0]); }
                catch (std::invalid_argument const&) { 
                    LOG_WARNING("Invalid float for vec2, parameter 0");
                    return false;
                }
                try { val1 = std::stof(comps[1]); }
                catch (std::invalid_argument const&) { 
                    LOG_WARNING("Invalid float for vec2, parameter 1");
                    return false;
                }
                material.addVec2Parameter(paramName, Vector2(val0, val1));
                return true;
            }
            else
            {
                LOG_WARNING("Too many vec2 parameters");
                return false;
            }
        }
        
        if (type == "vec3")
        {
            if (const std::vector<std::string> comps = Util::BreakString(value, ','); comps.size() == 3)
            {
                float val0, val1, val2;
                try { val0 = std::stof(comps[0]); }
                catch (std::invalid_argument const&) { 
                    LOG_WARNING("Invalid float for vec3, parameter 0");
                    return false;
                }
                try { val1 = std::stof(comps[1]); }
                catch (std::invalid_argument const&) { 
                    LOG_WARNING("Invalid float for vec3, parameter 1");
                    return false;
                }
                try { val2 = std::stof(comps[2]); }
                catch (std::invalid_argument const&) { 
                    LOG_WARNING("Invalid float for vec3, parameter 2");
                    return false;
                }
                material.addVec3Parameter(paramName, Vector3(val0, val1, val2));
                return true;
            }
            else
            {
                LOG_WARNING("Too many vec3 parameters");
                return false;
            }
        }
        
        if (type == "vec4")
        {
            if (const std::vector<std::string> comps = Util::BreakString(value, ','); comps.size() == 4)
            {
                float val0, val1, val2, val3;
                try { val0 = std::stof(comps[0]); }
                catch (std::invalid_argument const&) { 
                    LOG_WARNING("Invalid float for vec4, parameter 0");
                    return false;
                }
                try { val1 = std::stof(comps[1]); }
                catch (std::invalid_argument const&) { 
                    LOG_WARNING("Invalid float for vec4, parameter 1");
                    return false;
                }
                try { val2 = std::stof(comps[2]); }
                catch (std::invalid_argument const&) { 
                    LOG_WARNING("Invalid float for vec4, parameter 2");
                    return false;
                }
                try { val3 = std::stof(comps[3]); }
                catch (std::invalid_argument const&) { 
                    LOG_WARNING("Invalid float for vec4, parameter 3");
                    return false;
                }
                material.addVec4Parameter(paramName, Vector4(val0, val1, val2, val3));
                return true;
            }
            else
            {
                LOG_WARNING("Too many vec4 parameters");
                return false;
            }
        }
        
        LOG_WARNING("Unknown type");
        return false;
    }
    
    MaterialFile MaterialFile::readMaterial(const std::string& path)
    {
        MaterialFile material;
    
        std::ifstream file(path);
    
        if (!file.is_open())
        {
            LOG_WARNING("Material file not found or corrupted at " + path);
            return material;
        }
        
        uint32_t lineCount = 0;
        std::string line;
        
        while (std::getline(file, line))
        {
            lineCount ++;
            if (line.empty()) continue; // Skip if empty line
        
            line.erase(remove(line.begin(), line.end(), ' '), line.end()); // Remove whitespace
            line.erase(remove(line.begin(), line.end(), '"'), line.end()); // Remove quotes
            if (const size_t first = line.find('#'); first != std::string::npos) line.erase(first); // Remove comments from #
            if (line.empty()) continue; // Reskip empty line in case of full commented line
        
            // equals represent substrings separated by '=' equals[0] -> declaration, equals[1] -> value
            if (const std::vector<std::string> equals = Util::BreakString(line, '='); equals.size() == 2)
            {
                if (equals[0] == "texture") material.addTexture(equals[1]);
                else if (equals[0] == "shader") material.setShader(equals[1]);
                
                // dots represent strings separated by ':' dots[0] -> type, dots[1] -> name
                else if (const std::vector<std::string> dots = Util::BreakString(equals[0], ':'); dots.size() == 2)
                {
                    const std::string& type = dots[0];
                    const std::string& paramName = dots[1];

                    if (const std::string& value = equals[1]; !value.empty())
                    {
                        if (!handleTypes(type, value, paramName, material))
                        {
                            LOG_WARNING("Details above, bad type at line " + std::to_string(lineCount) + " in file : " + path);
                        }
                    }
                }
                else LOG_WARNING("Line " + std::to_string(lineCount) + " malformed in file " + path);
            }
            else LOG_WARNING("Line " + std::to_string(lineCount) + " malformed in file " + path);
        }
        
        file.close();
        
        return material;
    }
}