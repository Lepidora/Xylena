//Required includes
#include "stdafx.h"
#include "Update.h"

//System includes
#include <vector>

//Local includes
#include "Stage.h"
#include "StageHandler.h"
#include "GameObject.h"

namespace Xylena {

	Update::Update() {}

	Update::~Update() {}

	void Update::update() {
		StagePtr stage = StageHandler::getCurrentStage();
        
        if (stage) {
            
            std::vector<GameObjectPtr> gameObjects = stage->getObjects();
            
            ///Pre-update loop. Loops through every object and calls the preUpdate method
            for (unsigned preUpdateIndex = 0; preUpdateIndex < gameObjects.size(); preUpdateIndex++) {
                GameObjectPtr gameObject = gameObjects.at(preUpdateIndex);
                gameObject->preUpdate();
            }
            
            ///Update loop. Loops through every object and calls the update method
            for (unsigned updateIndex = 0; updateIndex < gameObjects.size(); updateIndex++) {
                GameObjectPtr gameObject = gameObjects.at(updateIndex);
                gameObject->update();
            }
            
            ///Post-update loop. Loops through every object and calls the postUpdate method
            for (unsigned postUpdateIndex = 0; postUpdateIndex < gameObjects.size(); postUpdateIndex++) {
                GameObjectPtr gameObject = gameObjects.at(postUpdateIndex);
                gameObject->postUpdate();
            }
            
        }

	}
}