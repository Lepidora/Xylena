#pragma once

namespace Xylena {

	class Coordinate {
	private:
		float xCoord;
		float yCoord;
		float zCoord;

		bool valuesSet;
	public:
		Coordinate();
        Coordinate(float _xCoord, float _yCoord);
		Coordinate(float _xCoord, float _yCoord, float _zCoord);
		~Coordinate();

		///Allows the setting of values after the coordinate has been initiated
		void setValues(float _xCoord, float _yCoord, float _zCoord);

		///Gets whether the coordinates have actually been set or if they are just defaultly initiated
		bool isSet();

		float getX() { return xCoord; };
		float getY() { return yCoord; };
		float getZ() { return zCoord; };

	};
}

