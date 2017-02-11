#pragma once

//System includes
#include <unordered_set>

//Local includes
#include "GameObject.h"
#include "Input.h"

namespace Xylena {
    
    class EventHandler {
    private:
        static std::unordered_set<GameObject *> registeredObjects;
        static std::unordered_set<GameObject *> previousObjects;
        
        static std::unordered_set<GameObject *> currentDown;
        
        //static std::vector<InputEvent> mouseEvents;
        
        static void processMouseEvents();
    public:
        
        static void processEvents();
        
        static void registerMouseEvent(GameObject *object);
        static void unregisterMouseEvent(GameObject *object);
        
        static void removeObject(GameObject *object);
        
    };
    
}