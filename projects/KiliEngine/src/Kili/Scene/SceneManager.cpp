#include "klpch.h"
#include "SceneManager.h"

std::vector<Kili::Scene*> Kili::SceneManager::mScenes = {};
unsigned int Kili::SceneManager::mCurrentSceneIndex = 0;

int Kili::SceneManager::mPendingNewScene = -1;
bool Kili::SceneManager::mPendingReload = false;

void Kili::SceneManager::loadScene(const int index)
{
    currentScene()->unload();
    
    mCurrentSceneIndex = index;
    currentScene()->init();
    currentScene()->load();
}

void Kili::SceneManager::reloadScene()
{
    currentScene()->unload();
    
    currentScene()->init();
    currentScene()->load();
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

void Kili::SceneManager::update()
{
    currentScene()->update();
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
