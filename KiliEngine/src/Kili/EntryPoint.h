#pragma once

#include "Engine.h"

extern Kili::Engine* Kili::createEngine();

int main(int argc, char** argv)
{
    auto engine = Kili::createEngine();
    engine->run();
    delete engine;
}