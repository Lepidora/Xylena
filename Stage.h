#pragma once

//System includes
#include <vector>
#include <memory>
#include <map>

//Local includes

namespace Xylena {

	class GameObject;
	typedef std::shared_ptr<GameObject> GameObjectPtr;

	class StageCamera;
	typedef std::shared_ptr<StageCamera> StageCameraPtr;

	class Stage {
	private:
		std::vector<GameObjectPtr> gameObjects;
		StageCameraPtr activeCamera;
        std::vector<GameObject *> removalQueue;
        
        ///Method to load resources necessary for a stage to exist
        virtual void load() {};
    
	public:
		~Stage();

		///Object manipulation
		virtual void addObject(GameObjectPtr object);
		virtual void addObjects(std::vector<GameObjectPtr> objects);
		virtual void setObjects(std::vector<GameObjectPtr> objects);
        virtual void removeObject(GameObject *object);
		virtual void setActiveCamera(StageCameraPtr camera);
        virtual void clean();

		///Object retrieval
		std::vector<GameObjectPtr> getObjects();
		StageCameraPtr getActiveCamera() { return activeCamera; };
	};

	//Typedefs
	typedef std::shared_ptr<Stage> StagePtr;
	
}