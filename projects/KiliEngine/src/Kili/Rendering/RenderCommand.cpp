#include "klpch.h"
#include "RenderCommand.h"

#include "Kili/Rendering/GraphicApi/OpenGl/OpenGlRendererApi.h"

Kili::RendererApi* Kili::RenderCommand::mApi = RendererApi::create();