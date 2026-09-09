#pragma once

namespace Kili
{
    enum class GraphicApi : char
    {
        None,
        OpenGl,
    };

    constexpr GraphicApi GRAPHIC_API = GraphicApi::OpenGl; // TODO change this in a renderer ore smth
    
#define BIT(offset) (1 << offset)
}
