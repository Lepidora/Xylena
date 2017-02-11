#pragma once

//System includes
#include <memory>

//Local includes
#include "Coordinate.h"

namespace Xylena {

	class Bounds {
	private:
		Coordinate topLeft;
		Coordinate bottomRight;

	public:
		Bounds(){};
		~Bounds(){};

		Bounds(Coordinate topLeft, Coordinate bottomRight);

		Coordinate getTopLeft() { return topLeft; };
		Coordinate getBottomRight() { return bottomRight; };

		void setTopLeft(Coordinate _topLeft) { topLeft = _topLeft; };
		void setBottomRight(Coordinate _bottomRight) { bottomRight = _bottomRight; };
	};

	//Typedefs
	typedef std::shared_ptr<Bounds> BoundsPtr;
}
