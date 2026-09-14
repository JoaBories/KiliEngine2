#include "klpch.h"
#include "RenderCommand.h"

#include "Kili/Renderer/GraphicApi/OpenGl/OpenGlRendererApi.h"

Kili::RendererApi* Kili::RenderCommand::mApi = RendererApi::create();