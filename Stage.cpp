#include "stdafx.h"
#include "Stage.h"

//Local includes
#include "GameObject.h"
#include "EventHandler.h"

namespace Xylena {

	Stage::~Stage() {
		gameObjects.empty();
	}

	void Stage::addObject(GameObjectPtr object) {
        object->setStage(this);
        gameObjects.push_back(object);
	}

	void Stage::addObjects(std::vector<GameObjectPtr> objects) {
        
        for (GameObjectPtr object: objects) {
            addObject(object);
        }
	}

	void Stage::setObjects(std::vector<GameObjectPtr> objects) {
		gameObjects = objects;
        
        for (GameObjectPtr object: objects) {
            object->setStage(this);
        }
	}

	void Stage::setActiveCamera(StageCameraPtr camera) {
		activeCamera = camera;
	}

	std::vector<GameObjectPtr> Stage::getObjects() {
		return gameObjects;
	}
    
    void Stage::removeObject(GameObject *object) {
        removalQueue.push_back(object);
    }
    
    void Stage::clean() {
        
        for (auto queueIt = removalQueue.begin(); queueIt != removalQueue.end(); queueIt++) {
            for (auto it = gameObjects.begin(); it != gameObjects.end(); it++) {
                if (it->get() == *queueIt) {
                    gameObjects.erase(it);
                    
                    it--;
                }
            }
        }
        
        removalQueue.clear();
        
    }
    
    void Stage::submitTransaction(Xylena::Transaction *transaction) {
        transactions.push_back(transaction);
    }
    
    void Stage::executeTransactions() {
        for (auto it = transactions.begin(); it != transactions.end(); it++) {
            Transaction *transaction = *it;
            transaction->execute();
        }
    }
}