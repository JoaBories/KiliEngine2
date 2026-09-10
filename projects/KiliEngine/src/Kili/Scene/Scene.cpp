#include "klpch.h"
#include "Scene.h"

void Kili::Scene::init()
{
    //init whatever to init
    
    load();
}

void Kili::Scene::update()
{
    //update actors
}

void Kili::Scene::unload()
{
    onClose();
}
