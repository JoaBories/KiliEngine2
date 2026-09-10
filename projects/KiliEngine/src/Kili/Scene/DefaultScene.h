#pragma once

#include "Scene.h"

namespace Kili
{
    class DefaultScene : public Scene
    {
        void onClose() override {}
        void load() override {}
        void onUpdate() override {}

    public:
        [[nodiscard]] std::string getName() const override { return "DefaultScene"; }
    };
}
