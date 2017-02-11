#include "Collision.h"

//System includes
#include <vector>

//Local includes
#include "StageHandler.h"


namespace Xylena {
    
    void Collision::calculateCollisions() {
        
        StagePtr currentStage = StageHandler::getCurrentStage();
        std::vector<GameObjectPtr> currentObjects = currentStage->getObjects();
        
        for (GameObjectPtr object: currentObjects) {
            
            LocationPtr objectLocation = object->getLocation();
            if (!objectLocation->isEtherial()) {
                
                for (GameObjectPtr secondObject: currentObjects) {
                    if (secondObject.get() != object.get()) {
                        
                        LocationPtr secondLocation = secondObject->getLocation();
                        if (!secondLocation->isEtherial()) {
                            
                            if (objectLocation->isLocationIntersecting(secondLocation)) {
                                //printf("Collision!!\n");
                                object->collide(secondObject.get());
                            }
                            
                        }
                        
                    }
                }
                
            }
        }
        
    }
    
    bool Collision::doObjectsIntersect(GameObjectPtr first, GameObjectPtr second) {
        
        
        
        
        return false;
    }
    
}