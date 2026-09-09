#pragma once

//ADDAPI
namespace Kili
{
    enum class GraphicApi : char
    {
        None = 0,
        OpenGl = 1,
    };
    
    inline std::string toString(const GraphicApi e)
    {
        switch (e)
        {
            case GraphicApi::None: return "None";
            case GraphicApi::OpenGl: return "OpenGl";
        }
        
        return "Unknown";
    }
    
    class Renderer
    {
    private:
        static GraphicApi mGraphicApi;
        
    public:
        static GraphicApi getApi() { return mGraphicApi; }
        static std::string getApiName() { return toString(mGraphicApi); }
    };
}
