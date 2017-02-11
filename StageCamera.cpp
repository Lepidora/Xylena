#include "stdafx.h"
#include "StageCamera.h"

//Local includes
#include "Location.h"

namespace Xylena {

	StageCamera::StageCamera() {
		location = LocationPtr(new Location);
		this->location->setEtherial(true);
		scalingFactor = 1.0;
	}

	StageCamera::~StageCamera() {}

	void StageCamera::setBounds(Bounds _viewBounds) {
		viewBounds = _viewBounds;
		//printf("Setting bounds x: %g, y: %g\n", viewBounds.getBottomRight().getX(), viewBounds.getBottomRight().getY());
	}

    Coordinate StageCamera::getViewportSize() {
        return viewBounds.getBottomRight();
    }

	//Takes the size of the view (usually screen resolution), a scaling factor and the camera's coordinates in the stage to calculate the bounds that the camera can see
	Bounds StageCamera::calculateBoundsForView() {

		Bounds worldBounds;
		Coordinate topLeft;
		Coordinate bottomRight;

		//printf("Calculating with bounds x: %g, y: %g\n", viewBounds.getBottomRight().getX(), viewBounds.getBottomRight().getY());

		//Calculate the scaled offsets from the camera coordinate that the bounds will be
		float xOffset = (viewBounds.getBottomRight().getX() / 2) * scalingFactor;
		float yOffset = (viewBounds.getBottomRight().getY() / 2) * scalingFactor;

		Coordinate cameraCoordinates = location->getCoordinates();

		//Sets the values of the bounds with the offsets
		topLeft.setValues(cameraCoordinates.getX() - xOffset, cameraCoordinates.getY() - yOffset, 0.0);
		bottomRight.setValues(cameraCoordinates.getX() + xOffset, cameraCoordinates.getY() + yOffset, 0.0);

		//Sets the final bound's coordinates
		worldBounds.setTopLeft(topLeft);
		worldBounds.setBottomRight(bottomRight);

        //printf("World Bounds: x1:%f, y1:%f, x2:%f, y2:%f\n", topLeft.getX(), topLeft.getY(), bottomRight.getX(), bottomRight.getY());

		return worldBounds;
	}
    Coordinate StageCamera::calculateTopLeftForView() {
        
        Coordinate topLeft;

        float xOffset = (viewBounds.getBottomRight().getX() / 2) * scalingFactor;
        float yOffset = (viewBounds.getBottomRight().getY() / 2) * scalingFactor;

        Coordinate cameraCoordinates = location->getCoordinates();

        topLeft.setValues(cameraCoordinates.getX() - xOffset, cameraCoordinates.getY() - yOffset, 0.0);

        return topLeft;

    }
}