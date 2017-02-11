#pragma once

//System includes
#include <memory>

//Local includes
#include "GameObject.h"
#include "Bounds.h"

namespace Xylena {

    class GameObject;

	class StageCamera: public GameObject {
	private:
		Bounds viewBounds;
		float scalingFactor;
	public:
		StageCamera();
		~StageCamera();

		void setBounds(Bounds _viewBounds);
        Coordinate getViewportSize();

		Bounds calculateBoundsForView();
        Coordinate calculateTopLeftForView();

        void setScalingFactor(float factor) { scalingFactor = factor; };
        float getScalingFactor() { return scalingFactor; };
	};

	//Typedefs
	typedef std::shared_ptr<StageCamera> StageCameraPtr;
}
