#pragma once
#include "GameActor.h"

/**
 * Scene, container for all the actors and systems in the level.
 * Each scene represent a level.
 * Only one scene at a time is loaded by the scene manager.
 */

namespace Kili
{
    class Scene
    {
        friend class SceneManager;
    
    private:
        std::vector<GameActor*> mActors;
    
        void init();
        void update();
    
        void unload();
        /** Called when game closed, scene changed or reloaded **/
        virtual void onClose() = 0;
    
        /** Should load initial actors, components and systems here **/
        virtual void load() = 0;
    
        /** Used to add logic outside actors **/
        virtual void onUpdate() = 0;
    
    public:
        virtual ~Scene() = default;

        [[nodiscard]] virtual std::string getName() const = 0;
    
    };
}