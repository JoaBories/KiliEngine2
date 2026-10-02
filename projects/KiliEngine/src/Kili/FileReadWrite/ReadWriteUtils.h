#pragma once

namespace Kili::Util
{
    /** 
     * Break a string into multiple substring divided by the delimiter. \n
     * Ex : "float:diffuse" and ':' will return { "float", "diffuse" }
     **/
    inline std::vector<std::string> BreakString(const std::string& str, const char delimiter)
    {
        std::vector<std::string> strings;
        std::string temp = str;
        size_t pos = temp.find(delimiter);
        
        while (pos != std::string::npos)
        {
            strings.emplace_back(temp.substr(0, pos));
            temp = temp.substr(pos + 1);
            pos = temp.find(delimiter);
        }
        strings.push_back(temp);
        
        return strings;
    }    
    
    /**
     * Convert string to bool. "0" or "false" -> false, "1" or "true" -> true
     * throw invalid_argument if not bale to convert.
     **/
    inline bool ToBool(const std::string& str)
    {
        if (str.empty()) throw std::invalid_argument("Empty string");
    
        if (str == "0" || str == "false") return false;
        if (str == "1" || str == "true") return true;
        
        throw std::invalid_argument("Invalid string");
    }
}
