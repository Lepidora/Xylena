#include "stdafx.h"
#include "Bounds.h"

namespace Xylena {

	Bounds::Bounds(Coordinate _topLeft, Coordinate _bottomRight) {
		//printf("Coords: x: %g, y: %g\n", _bottomRight.getX(), _bottomRight.getY());
		topLeft = _topLeft;
		bottomRight = _bottomRight;
	}
}