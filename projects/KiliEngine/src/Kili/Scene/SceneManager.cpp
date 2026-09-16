#include "klpch.h"
#include "SceneManager.h"

std::vector<Kili::Scene*> Kili::SceneManager::mScenes = {};
unsigned int Kili::SceneManager::mCurrentSceneIndex = 0;

int Kili::SceneManager::mPendingNewScene = -1;
bool Kili::SceneManager::mPendingReload = false;

void Kili::SceneManager::loadScene(const int index)
{
    mCurrentSceneIndex = index;
    currentScene()->init();
}

void Kili::SceneManager::reloadScene()
{
    currentScene()->unload();
    
    currentScene()->init();
}

int Kili::SceneManager::findScene(const std::string& sceneName)
{
    for (size_t i = 0; i < mScenes.size(); ++i)
    {
        if (mScenes[i]->getName() == sceneName) return static_cast<int>(i);
    }
    
    return -1;
}

void Kili::SceneManager::close()
{
    currentScene()->unload();
    for (const Scene* scene : mScenes) delete scene;
    mScenes.clear();
}

void Kili::SceneManager::loadReload()
{
    if (mPendingNewScene != -1)
    {
        currentScene()->unload();
    
        loadScene(mPendingNewScene);
        mPendingNewScene = -1;
        return;
    }
    
    if (mPendingReload)
    {
        reloadScene();
        mPendingReload = false;
        return;
    }
}

void Kili::SceneManager::onEvent(const IEvent& event)
{
    if (currentScene()) currentScene()->onEvent(event);
}

void Kili::SceneManager::update()
{
    currentScene()->update();
}

void Kili::SceneManager::render()
{
    currentScene()->render();
}

bool Kili::SceneManager::nextScene(const std::string& nextScene)
{
    if (const int index = findScene(nextScene) != -1)
    {
        mPendingNewScene = index;
        return true;
    }
    
    return false;
}
