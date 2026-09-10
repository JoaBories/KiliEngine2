#include "klpch.h"
#include "ConfigINI.h"

#include "Kili/Core/Logger/Log.h"

std::string Kili::ConfigINI::getString(const std::string& section, const std::string& key, const std::string& defaultVal) const
{
    if (mValues.find(section) != mValues.end())
    {
        if (mValues.at(section).find(key) != mValues.at(section).end())
        {
            return mValues.at(section).at(key);
        }
        else LOG_WARNING("No Key: " + key + " in Section: " + section + " of file: " + mName);
    }
    else LOG_WARNING("No Section: " + section + " in file: " + mName);
    
    return defaultVal;
}

bool Kili::ConfigINI::getBool(const std::string& section, const std::string& key, const bool defaultVal) const
{
    const std::string value = getString(section, key);
    if (value.empty()) return defaultVal;
    
    if (value == "0" || value == "false") return false;
    if (value == "1" || value == "true") return true;
    
    LOG_WARNING("Not a bool at key:" + key + " in Section: " + section + " of file: " + mName);
    return defaultVal;
}

int Kili::ConfigINI::getInt(const std::string& section, const std::string& key, const int defaultVal) const
{
    const std::string value = getString(section, key);
    if (value.empty()) return defaultVal;
    
    int val;
    
    try { val = std::stoi(value); }
    catch (std::invalid_argument const&) {
        LOG_WARNING("Not a int at key:" + key + " in Section: " + section + " of file: " + mName);
        return defaultVal;
    }
    catch (std::out_of_range const&) {
        LOG_WARNING("Integer out of range at key:" + key + " in Section: " + section + " of file: " + mName);
        return defaultVal;
    }
    
    return val;
}

float Kili::ConfigINI::getFloat(const std::string& section, const std::string& key, const float defaultVal) const
{
    const std::string value = getString(section, key);
    if (value.empty()) return false;
    
    float val;
    
    try { val = std::stof(value); }
    catch (std::invalid_argument) { 
        LOG_WARNING("Not a float at key:" + key + " in Section: " + section + " of file: " + mName);
        return defaultVal;
    }
    
    return val;
}

Kili::ConfigINI Kili::ConfigINI::readFile(const std::string& path, const std::string& name, const bool debugLines)
{
    ConfigINI configFile(name);
    std::ifstream file(path);
    
    if (!file.is_open())
    {
        LOG_WARNING("Config File : " + name + " not found or corrupted at " + path);
        return configFile;
    }
    
    unsigned int lineCount = 0;
    
    std::string line;
    std::string currentSection;
    
    while (std::getline(file, line))
    {
        lineCount ++;
        if (line.empty()) continue; // Skip if empty line
        
        line.erase(remove(line.begin(), line.end(), ' '), line.end()); // Remove whitespace
        line.erase(remove(line.begin(), line.end(), '"'), line.end()); // Remove quotes
        if (const size_t first = line.find('#'); first != std::string::npos) line.erase(first); // Remove comments from #
        if (const size_t first = line.find(';'); first != std::string::npos) line.erase(first); // and ;
        if (line.empty()) continue; // Skip if full commented line
        
        if (line[0] == '[')
        {
            if (const size_t close = line.find(']', 1); close != std::string::npos) 
                currentSection = line.substr(1, close - 1);
            else 
                LOG_WARNING("Section malformed at line " + std::to_string(lineCount) + " in : " + name);
        }
        else if (const size_t separator = line.find('='); separator != std::string::npos)
            configFile.setString(currentSection, line.substr(0, separator), line.substr(separator+1, line.length()));

        else LOG_WARNING("Line " + std::to_string(lineCount) + " malformed");
        
        if (debugLines) LOG_INFO(line);
    }
    
    file.close();
    
    return configFile;
}
