#include "stdafx.h"
#include "Coordinate.h"
#include <stdio.h>

namespace Xylena {

	Coordinate::Coordinate() {
		valuesSet = false;

		xCoord = 0.0;
		yCoord = 0.0;
		zCoord = 0.0;
	}

    Coordinate::Coordinate(float _xCoord, float _yCoord) {
        setValues(_xCoord, _yCoord, 0.0);
    }

	Coordinate::Coordinate(float _xCoord, float _yCoord, float _zCoord) {
        setValues(_xCoord, _yCoord, _zCoord);
	}

	Coordinate::~Coordinate() {}

	void Coordinate::setValues(float _xCoord, float _yCoord, float _zCoord) {
		xCoord = _xCoord;
		yCoord = _yCoord;
		zCoord = _zCoord;

		valuesSet = true;
	}

	bool Coordinate::isSet() {
		return valuesSet;
	}
}