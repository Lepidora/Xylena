#pragma once

//System includes
#include <vector>
#include <memory>
#include <map>

//Local includes
#include "Stage.h"
#include "GameObject.h"

using namespace std;

namespace Xylena {

	class StageHandler {
	private:
		static StagePtr currentStage;
		static std::map<std::string, StagePtr> stages;
	public:
		StageHandler();
		~StageHandler();

		///Stage assignment
		static StagePtr setCurrentStageFromID(std::string id);
		static bool setCurrentStage(StagePtr stage);

		///Stage adding
		static void addStage(StagePtr stage, std::string id);

		///Stage getting
		static StagePtr getCurrentStage();
        
        ///Stage cleaning
        static void clean();

	};
}