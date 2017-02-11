#include "stdafx.h"
#include "Location.h"

//System includes
#include <cmath>

namespace Xylena {

	Location::Location() {
		etherial = false;
	}

	Location::~Location() {}

	void Location::setCoordinates(Coordinate _coordinates) {
		coordinates = _coordinates;
	}

	Coordinate Location::getCoordinates() {
		return coordinates;
	}

	void Location::setBounds(Bounds _bounds) {
		bounds = _bounds;

        Coordinate topLeft = bounds.getTopLeft();
        Coordinate bottomRight = bounds.getBottomRight();

        //Pre-calculate the absolute size of the bounds
        Coordinate size(std::abs(topLeft.getX()-bottomRight.getY()), std::abs(topLeft.getY()-bottomRight.getY()), std::abs(topLeft.getZ()-bottomRight.getZ()));

	}

	Bounds Location::getBounds() {
		return bounds;
	}

    void Location::setSize(Coordinate _size) {
        size = _size;

        float xOffset = size.getX() / 2;
        float yOffset = size.getY() / 2;
        float zOffset = size.getZ() / 2;

        Coordinate topLeft(0 - xOffset, yOffset, 0 - zOffset);
        Coordinate bottomRight(xOffset, 0 - yOffset, zOffset);

        bounds = Bounds(topLeft, bottomRight);

//#error Check this works properly

    }

    Coordinate Location::getSize() {
        return size;
    }

	void Location::setEtherial(bool _etherial) {
		etherial = _etherial;
	}

	bool Location::isEtherial() {
		return etherial;
	}

	bool Location::isWithin2DBounds(Bounds inputBounds) {
		if (etherial) {
			return false;
		} else {
			Coordinate topLeftCorner(bounds.getTopLeft().getX() + coordinates.getX(), bounds.getTopLeft().getY() + coordinates.getY(), 0.0);
			Coordinate bottomRightCorner(bounds.getBottomRight().getX() + coordinates.getX(), bounds.getBottomRight().getY() + coordinates.getY(), 0.0);
//#error debug this
			//This tests if the coordinates of the opposite sides of each square lie within each other
			if (topLeftCorner.getX() < inputBounds.getBottomRight().getX() &&
				bottomRightCorner.getX() > inputBounds.getTopLeft().getX() &&
				topLeftCorner.getY() > inputBounds.getBottomRight().getY() &&
				bottomRightCorner.getY() < inputBounds.getTopLeft().getY()) {
				return true;
			} else {
				return false;
			}
		}
	}
    
    bool Location::isPointWithin2DBounds(Coordinate inputCoord) {
        if (etherial) {
            return false;
        } else {
            Coordinate topLeftCorner(bounds.getTopLeft().getX() + coordinates.getX(), bounds.getTopLeft().getY() + coordinates.getY(), 0.0);
            Coordinate bottomRightCorner(bounds.getBottomRight().getX() + coordinates.getX(), bounds.getBottomRight().getY() + coordinates.getY(), 0.0);
            
            if (topLeftCorner.getX() < inputCoord.getX() &&
                bottomRightCorner.getX() > inputCoord.getX() &&
                topLeftCorner.getY() > inputCoord.getY() &&
                bottomRightCorner.getY() < inputCoord.getY()) {
                return true;
            } else {
                return false;
            }
        }
    }
    
    bool Location::isLocationIntersecting(LocationPtr inputLocation) {
        
        if (etherial || inputLocation->isEtherial()) {
            return false;
        }
        
        Bounds inputBounds = inputLocation->getBounds();
        
        Coordinate pos = inputLocation->getCoordinates();
        
        Coordinate topLeft = inputBounds.getTopLeft();
        Coordinate bottomRight = inputBounds.getBottomRight();
        
        Bounds testBounds;
        testBounds.setTopLeft(Coordinate(topLeft.getX() + pos.getX(), topLeft.getY() + pos.getY(), topLeft.getZ() + pos.getZ()));
        testBounds.setBottomRight(Coordinate(bottomRight.getX() + pos.getX(), bottomRight.getY() + pos.getY(), bottomRight.getZ() + pos.getZ()));
        
        if (isWithin2DBounds(testBounds)) {
            return true;
        } else {
            return false;
        }
    }
}