#pragma once

//Local includes
#include "GameObject.h"

namespace Xylena {
    
    class Collision {
    private:
    public:
        static void calculateCollisions();
        static bool doObjectsIntersect(GameObjectPtr first, GameObjectPtr second);
    };
}