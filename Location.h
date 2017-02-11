#pragma once

//System includes
#include <memory>

//Local includes
#include "Coordinate.h"
#include "Bounds.h"

namespace Xylena {
    
    
    

	class Location {
	private:
        
        //Typedefs
        typedef std::shared_ptr<Location> LocationPtr;
        
		bool etherial;

		///Coordinates within the game world
		Coordinate coordinates;

        ///Size of the object
        Coordinate size;

		///A square denoting the size of the object, relative to the location. This is assumed to be centered on the location's coordinates, with one coordinate being (0,0).
		Bounds bounds;
	public:
        
        
        
		Location();
		~Location();

		void setCoordinates(Coordinate _coordinates);
		Coordinate getCoordinates();

		void setBounds(Bounds _bounds);
		Bounds getBounds();

        void setSize(Coordinate size);
        Coordinate getSize();

		void setEtherial(bool _etherial);
		bool isEtherial();

		///Tests whether the location comes within the given bounds
		bool isWithin2DBounds(Bounds inputBounds);
        
        ///Tests whether a point is inside the location
        bool isPointWithin2DBounds(Coordinate inputCoord);

        ///Test if another location is intersecting this one
        bool isLocationIntersecting(LocationPtr location);
        
        
	};

    //Typedefs
    typedef std::shared_ptr<Location> LocationPtr;

}