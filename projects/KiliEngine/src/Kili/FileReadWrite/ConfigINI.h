#pragma once

//  INI Config File Format .ini
//
//  Grammar :
//  - KEY-value: key = value
//  - SECTIONS: [SectionName] -> all following KEYS belong to this SECTION
//  - Comments: lines beginning with ';' or '#'
//  - Case Sensitive: KEYS and SECTIONS require case sensitivity
//  - Multiline: does not support multiline
//
//  Supported Types :
//  String: as they are
//  Bool: 0/1 or true/false
//  Float: (+/-) x.x (e(-/+)x.x)
//  Int: (+/-) x
//
//  Malformed lines are ignored and produce a warning in logs.
//  Avoid duplicate KEYS in the same SECTION as only the last one will be considered.
//  Watch for Kili.ini for example.

namespace Kili
{
    class ConfigINI
    {
    private:
        std::string mName;
        
        /** Container for INI values. mValues[section][key] */
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> mValues;
        
    public:
        ConfigINI() = default;
        explicit ConfigINI(std::string name) : mName(std::move(name)) {}
        ~ConfigINI() = default;
        
        /** Return DefaultVal if key or section not found **/
        [[nodiscard]] std::string getString(const std::string& section, const std::string& key, const std::string& defaultVal = "") const;
        
        /** Return DefaultVal if key or section not found **/
        [[nodiscard]] bool getBool(const std::string& section, const std::string& key, bool defaultVal = false) const;
        
        /** Return DefaultVal if key or section not found **/
        [[nodiscard]] int getInt(const std::string& section, const std::string& key, int defaultVal = 0) const;
        
        /** Return DefaultVal if key or section not found **/
        [[nodiscard]] float getFloat(const std::string& section, const std::string& key, float defaultVal = 0.0f) const;
        
        void setString(const std::string& section, const std::string& key, const std::string& value) {
            mValues[section][key] = value; }
        
        void setBool(const std::string& section, const std::string& key, const bool value) { 
            mValues[section][key] = std::to_string(value); }
        
        void setInt(const std::string& section, const std::string& key, const int value) {
            mValues[section][key] = std::to_string(value); }
        
        void setFloat(const std::string& section, const std::string& key, const float value) {
            mValues[section][key] = std::to_string(value); }
        
        [[nodiscard]] static ConfigINI readFile(const std::string& path, const std::string& name, bool debugLines = false);
    };
}
