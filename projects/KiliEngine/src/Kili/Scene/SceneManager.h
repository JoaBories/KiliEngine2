#pragma once
#include "Scene.h"

/**
 * Scene Manager, singleton that hold all the Scenes and is responsible for their
 * loading, unloading.
*/

namespace Kili
{
    class SceneManager
    {
    	friend class Engine;
    	
    private :
    	static std::vector<Scene*> mScenes;
    	static unsigned int mCurrentSceneIndex;
    
    	// SceneManager wait for the end of update to load new scene or reload current one
    	static int mPendingNewScene;	/* "" represent nothing to do */
    	static bool mPendingReload;		/* true represent reload */
    
    	// Utility
    	static void loadScene(int index);
    	static void reloadScene();
    	static int findScene(const std::string& sceneName);
    	
    	// Methods used only by the Engine
    	/** Unload current scene and free mScenes **/
    	static void close();
    	
    	/** Use it during the first initialization of the engine **/
    	static void setScenes(const std::vector<Scene*>& scenes) { mScenes = scenes; }
    	
    	/** Load or Reload scenes depending on pending actions **/
    	static void loadReload();
    	
    	static void update();
    	
    public :
    	static Scene* currentScene() { return mScenes[mCurrentSceneIndex]; }
    	
    	/** take scene name and return false if scene is not found **/
    	static bool nextScene(const std::string& nextScene);
    };
}