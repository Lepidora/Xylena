//Essential includes
#include "stdafx.h"
#include "StageHandler.h"

namespace Xylena {

	//Static variable initialisation
	StagePtr StageHandler::currentStage = nullptr;
	std::map<std::string, StagePtr> StageHandler::stages;

	StageHandler::StageHandler() {}

	StageHandler::~StageHandler() {}

	StagePtr StageHandler::setCurrentStageFromID(std::string id) {

		StagePtr lookupStage;

		///If the map doesn't contain a stage for the specified ID, return nullptr
		try {
			lookupStage = stages.at(id);
		} catch (const std::exception&) {
			return nullptr;
		}

		currentStage = lookupStage;

		///Return the assigned stage so it can be manipulated
		return lookupStage;
	}

	bool StageHandler::setCurrentStage(StagePtr stage) {
		if (stage) {
			currentStage = stage;
			return true;
		} else {
			///Let the caller know the assignment failed
			return false;
		}
	}

	void StageHandler::addStage(StagePtr stage, std::string id) {
		stages.insert(std::pair<std::string, StagePtr>(id, stage));
	}

	StagePtr StageHandler::getCurrentStage() {
		return currentStage;
	}
    
    void StageHandler::clean() {
        
        if (currentStage) {
            currentStage->clean();
        }
        
        for (auto it = stages.begin(); it != stages.end(); it++) {
            if (it->second != nullptr && it->second != currentStage) {
                it->second->clean();
            }
        }
        
    }
}